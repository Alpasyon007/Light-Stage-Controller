// pigpio
#include <pigpio.h>
#include <signal.h>

#include <gphoto2/gphoto2-camera.h>

// std
#include <iostream>
#include <fstream>

// Helpers
#include "StepperMotorController.h"
#include "Serial.h"
#include "CaptureUtility.h"
#include "LEDController.h"

// // #define IMGUI_IMPL_OPENGL_LOADER_GLAD
// #include "backends/imgui_impl_opengl3.cpp"
// #include "backends/imgui_impl_glfw.cpp"

// DO NOT CHANGE (AT 31V)
#define MOTOR_MAX_STEP_DELAY_TIME 0.005f
// DO NOT CHANGE (AT 31V)

#define MOTOR_STEP_PIN 16
#define MOTOR_DIRECTION_PIN 21
#define MOTOR_STEP_DELAY_TIME 0.005f

void CameraCalibrationCapture(int turns /*= 10*/, LEDController& led, CaptureUtility& c, StepperMotorController& stepperMotor) {
	std::chrono::steady_clock::time_point capture_start = std::chrono::steady_clock::now();
	led.LightLED(LEDController::LED_MODE::ALL);
	for(int i = 0; i < turns; i++) {
		std::cout << "Turn " << i << std::endl;
		time_sleep(1);
		c.TriggerCapture();
		stepperMotor.StepForward(200/turns);
		time_sleep(1);
	}
	std::chrono::steady_clock::time_point capture_end = std::chrono::steady_clock::now();
	std::cout << "Camera Calibration Duration = " << std::chrono::duration_cast<std::chrono::seconds>(capture_end - capture_start).count() << "[s]" << std::endl;
}

void SingleViewPhotometricStereoCapture(LEDController& led, CaptureUtility& c, LEDController::LED_MODE mode) {
	std::chrono::steady_clock::time_point capture_start = std::chrono::steady_clock::now();

	for(int j = 108; j < 144; j += static_cast<int>(mode)) {
		std::cout << "LED: " << j << "," << " Capture " << (j)/static_cast<int>(mode) <<  std::endl;
		led.LightLED(j);
		c.TriggerCapture();
		time_sleep(1);
	}

	for(int j = 0; j < 36; j += static_cast<int>(mode)) {
		std::cout << "LED: " << j << "," << " Capture " << (j)/static_cast<int>(mode) <<  std::endl;
		led.LightLED(j);
		c.TriggerCapture();
		time_sleep(1);
	}

	std::chrono::steady_clock::time_point capture_end = std::chrono::steady_clock::now();
	std::cout << "Capture Session Duration = " << std::chrono::duration_cast<std::chrono::seconds>(capture_end - capture_start).count() << "[s]" << std::endl;
}

void MultiViewPhotometricStereoCapture(int turns /*= 10*/, LEDController& led, CaptureUtility& c, StepperMotorController& stepperMotor, LEDController::LED_MODE mode) {
	std::chrono::steady_clock::time_point capture_start = std::chrono::steady_clock::now();
	for(int i = 0; i < turns; i++) {
		std::cout << "Turn " << i << std::endl;
		time_sleep(1);

		for(int j = 0; j < 144; j += static_cast<int>(mode)) {
			std::cout << "LED: " << j << "," << " Capture " << (j + 1)/static_cast<int>(mode) <<  std::endl;
			led.LightLED(j);
			c.TriggerCapture();
		}

		stepperMotor.StepForward(200/turns);
		time_sleep(1);
	}
	std::chrono::steady_clock::time_point capture_end = std::chrono::steady_clock::now();
	std::cout << "Capture Session Duration = " << std::chrono::duration_cast<std::chrono::seconds>(capture_end - capture_start).count() << "[s]" << std::endl;

}

int main() {
	if (gpioInitialise() < 0) return -1;
	if(MOTOR_STEP_DELAY_TIME > MOTOR_MAX_STEP_DELAY_TIME) return -1;

	// All Controller and Utility Classes Initialisation
	LEDController led(LEDController::LED_MODE::SINGLE);
	CaptureUtility c;
	Serial serial("/dev/ttyUSB0", 9600);
	StepperMotorController stepperMotor(MOTOR_STEP_PIN, MOTOR_DIRECTION_PIN, MOTOR_STEP_DELAY_TIME);

	// Set Parameters
	c.CaptureToSD(true);

	// Test the motor
	// stepperMotor.StepForward(200); // 360 Degrees
	time_sleep(1);

	// Camera Calibration Capture
	CameraCalibrationCapture(10, led, c, stepperMotor);

	// Capture
	SingleViewPhotometricStereoCapture(led, c, LEDController::LED_MODE::SINGLE);

	gpioWrite(21, 0);
	gpioTerminate();
}