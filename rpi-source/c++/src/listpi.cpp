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

#include <gphoto2/gphoto2.h>
#include <gphoto2pp/camera_wrapper.hpp>
#include <gphoto2pp/camera_file_wrapper.hpp>
#include <gphoto2pp/helper_camera_wrapper.hpp>	

#include <gphoto2pp/camera_capture_type_wrapper.hpp>
#include <gphoto2pp/exceptions.hpp>

#include <gphoto2pp/window_widget.hpp>
#include <gphoto2pp/toggle_widget.hpp>
#include <gphoto2pp/radio_widget.hpp>

// DO NOT CHANGE (AT 31V)
#define MOTOR_MAX_STEP_DELAY_TIME 0.005f
// DO NOT CHANGE (AT 31V)

#define MOTOR_STEP_PIN 16
#define MOTOR_DIRECTION_PIN 21
#define MOTOR_STEP_DELAY_TIME 0.005f

void CaptureToSD(gphoto2pp::CameraWrapper& cameraWrapper, bool captureToSD) {
	try {
		auto captureWidget = cameraWrapper.getConfig().getChildByName<gphoto2pp::StringWidget>("capturetarget");
		captureWidget.setValue(captureToSD ? "Memory card" : "Internal Ram");
		cameraWrapper.setConfig(captureWidget);
	} catch (gphoto2pp::exceptions::gphoto2_exception& e) {
		std::cout << "GPhoto Exception Code: " << e.getResultCode() << std::endl;
		std::cout << "Exception Message: " << e.what() << std::endl;
	}
}

void CaptureImage(gphoto2pp::CameraWrapper& cameraWrapper) {
	try {
		std::cout << "Attempting Capture" << std::endl << std::endl;
		// Clean and quick capture and save to disk, but this assumes you are taking images, and in jpeg foramt. Adjust type and extension as appropriate.
		gphoto2pp::CameraFileWrapper cameraFileWrapper;
		gphoto2pp::helper::capture(cameraWrapper, cameraFileWrapper, false);
		std::cout << "Captured" << std::endl << std::endl;
	} catch (gphoto2pp::exceptions::gphoto2_exception& e) {
		std::cout << "GPhoto Exception Code: " << e.getResultCode() << std::endl;
		std::cout << "Exception Message: " << e.what() << std::endl;

		// Try Again
		CaptureImage(cameraWrapper);
	}
}

int main() {
	gp_context_new();
	if (gpioInitialise() < 0) return -1;

	if(MOTOR_STEP_DELAY_TIME > MOTOR_MAX_STEP_DELAY_TIME) return -1;

	std::cout << "connect to camera" << std::endl;
	gphoto2pp::CameraWrapper cameraWrapper; // Not passing in model and port will connect to the first available camera.	

	CaptureToSD(cameraWrapper, true);

	Serial serial("/dev/ttyUSB0", 9600);
	std::cout << "Initalised GPIO" << std::endl;
	StepperMotorController stepperMotor(MOTOR_STEP_PIN, MOTOR_DIRECTION_PIN, MOTOR_STEP_DELAY_TIME);

	stepperMotor.StepForward(200); // 360 Degrees
	time_sleep(1);
	

	auto start = std::chrono::high_resolution_clock::now();

	int turns = 10;

	for(int i = 0; i < turns; i++) {
		std::cout << "Turn " << i << std::endl;
		serial.Write(0);
		time_sleep(1);

		for(int j = 0; j < 144; j += 4) {
			std::cout << "LED: " << j << "," << " Capture " << (j + 1)/4 <<  std::endl;
			serial.Write(j);
			CaptureImage(cameraWrapper);
		}

		stepperMotor.StepForward(200/turns);
		time_sleep(1);
	}
	auto stop = std::chrono::high_resolution_clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::minutes>(stop - start);
	std::cout << duration.count() << std::endl;

	gpioWrite(21, 0);
	gpioTerminate();
}