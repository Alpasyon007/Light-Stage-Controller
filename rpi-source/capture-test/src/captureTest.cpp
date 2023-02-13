// std
#include <iostream>
#include <fstream>
#include<thread>

// Helpers
#include <gphoto2/gphoto2.h> 
#include <gphoto2/gphoto2-camera.h>
#include <gphoto2pp/camera_wrapper.hpp>
#include <gphoto2pp/camera_file_wrapper.hpp>
#include <gphoto2pp/helper_camera_wrapper.hpp>	

#include <gphoto2pp/camera_capture_type_wrapper.hpp>
#include <gphoto2pp/exceptions.hpp>

#include <gphoto2pp/window_widget.hpp>
#include <gphoto2pp/toggle_widget.hpp>
#include <gphoto2pp/radio_widget.hpp>

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
		std::cout << "Attempting Capture" << std::endl;
		// Clean and quick capture and save to disk, but this assumes you are taking images, and in jpeg foramt. Adjust type and extension as appropriate.
		gphoto2pp::CameraFileWrapper cameraFileWrapper;
		gphoto2pp::helper::capture(cameraWrapper, cameraFileWrapper, false);

		std::cout << "Captured" << std::endl << std::endl;
	} catch (gphoto2pp::exceptions::gphoto2_exception& e) {
		// if(e.getResultCode()  != -110) {
			std::cout << "GPhoto Exception Code: " << e.getResultCode() << std::endl;
			std::cout << "Exception Message: " << e.what() << std::endl;
		// }

		// Try Again
		CaptureImage(cameraWrapper);
	}
}

void TriggerCapture(gphoto2pp::CameraWrapper& cameraWrapper) {
	try {
		std::cout << "Attempting Capture" << std::endl;
		// Trigger camera capture
		cameraWrapper.triggerCapture();
		
		// Let I/O Finish
		std::this_thread::sleep_for(std::chrono::milliseconds(1250));

		std::cout << "Captured" << std::endl << std::endl;
	} catch (gphoto2pp::exceptions::gphoto2_exception& e) {
		// if(e.getResultCode()  != -110) {
			std::cout << "GPhoto Exception Code: " << e.getResultCode() << std::endl;
			std::cout << "Exception Message: " << e.what() << std::endl;
		// }

		// Try Again
		TriggerCapture(cameraWrapper);
	}
}

int main() {
	gp_context_new();

	std::cout << "connect to camera" << std::endl;
	gphoto2pp::CameraWrapper cameraWrapper; // Not passing in model and port will connect to the first available camera.	

	CaptureToSD(cameraWrapper, true);

	{
		std::chrono::steady_clock::time_point capture_start = std::chrono::steady_clock::now();
		int captures = 10;
		for(int i = 0; i < captures; i++) {	
			std::cout << "----Capture " << i << " ----" << std::endl;
			std::chrono::steady_clock::time_point individual_capture_start = std::chrono::steady_clock::now();
			CaptureImage(cameraWrapper);
			std::this_thread::sleep_for(std::chrono::milliseconds(2000));
			std::chrono::steady_clock::time_point individual_capture_end = std::chrono::steady_clock::now();
			std::cout << "Capture Time = " << std::chrono::duration_cast<std::chrono::seconds>(individual_capture_end - individual_capture_start).count() << "[s]" << std::endl;
		}
		std::chrono::steady_clock::time_point capture_end = std::chrono::steady_clock::now();
		std::cout << "Total Capture Session Duration = " << std::chrono::duration_cast<std::chrono::seconds>(capture_end - capture_start).count() << "[s]" << std::endl;
	}

	{
		std::chrono::steady_clock::time_point capture_start = std::chrono::steady_clock::now();
		int captures = 10;
		for(int i = 0; i < captures; i++) {	
			std::cout << "----Capture " << i << " ----" << std::endl;
			TriggerCapture(cameraWrapper);
		}
		std::chrono::steady_clock::time_point capture_end = std::chrono::steady_clock::now();
		std::cout << "Total Capture Session Duration = " << std::chrono::duration_cast<std::chrono::seconds>(capture_end - capture_start).count() << "[s]" << std::endl;
	}
}