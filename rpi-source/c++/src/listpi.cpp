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
#include <gphoto2pp/camera_wrapper.hpp> 		// Header for CameraWrapper
#include <gphoto2pp/camera_file_wrapper.hpp>	// Header for CameraFileWrapper
#include <gphoto2pp/helper_camera_wrapper.hpp>	// Used for helper::capture(...) method

#include <gphoto2pp/camera_capture_type_wrapper.hpp>
#include <gphoto2pp/exceptions.hpp>

#include <gphoto2pp/window_widget.hpp>
#include <gphoto2pp/toggle_widget.hpp>
#include <gphoto2pp/radio_widget.hpp>

#define MOTOR_STEP_PIN 16
#define MOTOR_DIRECTION_PIN 21
#define MOTOR_STEP_DELAY_PIN 0.09f

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
		std::cout << "Taking picture" << std::endl << std::endl;
		// Clean and quick capture and save to disk, but this assumes you are taking images, and in jpeg foramt. Adjust type and extension as appropriate.
		gphoto2pp::CameraFileWrapper cameraFileWrapper;
		gphoto2pp::helper::capture(cameraWrapper, cameraFileWrapper, false);
	} catch (gphoto2pp::exceptions::gphoto2_exception& e) {
		std::cout << "GPhoto Exception Code: " << e.getResultCode() << std::endl;
		std::cout << "Exception Message: " << e.what() << std::endl;
	}
}

int main() {
	gp_context_new();
	if (gpioInitialise() < 0) return -1;

	std::cout << "connect to camera" << std::endl;
	gphoto2pp::CameraWrapper cameraWrapper; // Not passing in model and port will connect to the first available camera.	

	CaptureToSD(cameraWrapper, true);

	Serial serial("/dev/ttyUSB0", 9600);
	std::cout << "Initalised GPIO" << std::endl;
	StepperMotorController stepperMotor(MOTOR_STEP_PIN, MOTOR_DIRECTION_PIN, MOTOR_STEP_DELAY_PIN);

	while(true) {
		stepperMotor.StepForward(200); // 360 Degrees
		time_sleep(1);

		for(int i = 0; i < 10; i++) {
			serial.Write(0);
			time_sleep(1);

			for(int i = 0; i < 144; i++) {
				CaptureImage(cameraWrapper);
				serial.Write(i);
				time_sleep(1);
			}

			stepperMotor.StepForward(20);
			time_sleep(1);
		}
	}

		gpioWrite(21, 0);
	gpioTerminate();
}