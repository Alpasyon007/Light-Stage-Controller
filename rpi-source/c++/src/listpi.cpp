// pigpio
#include <pigpio.h>
#include <signal.h>

// gphoto
#include <gphoto2/gphoto2-camera.h>

// std
#include <iostream>
#include <fstream>

// Helpers
#include "StepperMotorController.h"
#include "Serial.h"
#include "CaptureUtility.h"
#include "LEDController.h"

// DO NOT CHANGE (AT 31V)
#define MOTOR_MAX_STEP_DELAY_TIME 0.05f
// DO NOT CHANGE (AT 31V)

#define MOTOR_STEP_PIN 16
#define MOTOR_DIRECTION_PIN 21
#define MOTOR_STEP_DELAY_TIME 0.01f

void WaitForFocus() {
	do {
	std::cout << '\n' << "Refocus camera for new view, Press a key to continue..." << std::endl;
	} while (std::cin.get() != '\n');
}

void CameraCalibrationCapture(int turns /*= 10*/, LEDController& led, CaptureUtility& c, StepperMotorController& stepperMotor) {
	std::chrono::steady_clock::time_point capture_start = std::chrono::steady_clock::now();
	led.LightLED(LEDController::LED_MODE::ALL);
	for(int i = 0; i < turns; i++) {
		std::cout << "Turn " << i << std::endl;
		time_sleep(0.5f);
		c.TriggerCapture();
		time_sleep(5);
		stepperMotor.StepForward(200/turns);
	}
	std::chrono::steady_clock::time_point capture_end = std::chrono::steady_clock::now();
	std::cout << "Camera Calibration Duration = " << std::chrono::duration_cast<std::chrono::seconds>(capture_end - capture_start).count() << "[s]" << std::endl;
}

void SingleViewPhotometricStereoCapture(LEDController& led, CaptureUtility& c, LEDController::LED_MODE mode) {
	std::chrono::steady_clock::time_point capture_start = std::chrono::steady_clock::now();

	constexpr float sleepTime = 1.1f;

	auto capture = [&](int j) {
		std::cout << "LED: " << j << "," << " Capture " << (j)/static_cast<int>(LEDController::LED_MODE::SINGLE) <<  std::endl;
		led.LightLED(j);
		time_sleep(0.3f);
		c.TriggerCapture();
		time_sleep(sleepTime);
	};

	for(int j = 108; j < 143; j += static_cast<int>(LEDController::LED_MODE::SINGLE)) {
		capture(j);
		capture(107 + j);
	}

	for(int j = 0; j < 37; j += static_cast<int>(LEDController::LED_MODE::SINGLE)) {
		capture(j);
		capture(251 + j);
	}

	std::chrono::steady_clock::time_point capture_end = std::chrono::steady_clock::now();
	std::cout << "Capture Session Duration = " << std::chrono::duration_cast<std::chrono::seconds>(capture_end - capture_start).count() << "[s]" << std::endl;
}

void MultiViewPhotometricStereoCapture(int turns /*= 10*/, LEDController& led, CaptureUtility& c, StepperMotorController& stepperMotor, LEDController::LED_MODE mode) {
	std::chrono::steady_clock::time_point capture_start = std::chrono::steady_clock::now();
	for(int i = 0; i < turns; i++) {
		std::cout << "Turn " << i << std::endl;
		time_sleep(2);

		SingleViewPhotometricStereoCapture(led, c, mode);
		stepperMotor.StepForward(200/turns);

		// WaitForFocus();

		time_sleep(2);
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
	stepperMotor.StepForward(200); // 360 Degrees
	time_sleep(1);

	// Camera Calibration Capture
	// CameraCalibrationCapture(10, led, c, stepperMotor);

	// Capture
	// SingleViewPhotometricStereoCapture(led, c, LEDController::LED_MODE::SINGLE);
	MultiViewPhotometricStereoCapture(10, led, c, stepperMotor, LEDController::LED_MODE::SINGLE);

	gpioWrite(21, 0);
	gpioTerminate();
}