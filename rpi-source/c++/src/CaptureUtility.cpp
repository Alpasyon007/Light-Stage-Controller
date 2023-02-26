#include "CaptureUtility.h"
#include <iostream>

#define TRIGGER_DELAY 1250


CaptureUtility::CaptureUtility() : m_cameraWrapper() {
		std::cout << "connect to camera" << std::endl;
		gp_context_new();
}

void CaptureUtility::CaptureToSD(bool captureToSD) {
	try {
		auto captureWidget = m_cameraWrapper.getConfig().getChildByName<gphoto2pp::StringWidget>("capturetarget");
		captureWidget.setValue(captureToSD ? "Memory card" : "Internal Ram");
		m_cameraWrapper.setConfig(captureWidget);
	} catch (gphoto2pp::exceptions::gphoto2_exception& e) {
		std::cout << "GPhoto Exception Code: " << e.getResultCode() << std::endl;
		std::cout << "Exception Message: " << e.what() << std::endl;
	}
}

void CaptureUtility::CaptureImage() {
	try {
		std::cout << "Attempting Capture" << std::endl << std::endl;
		// Clean and quick capture and save to disk, but this assumes you are taking images, and in jpeg foramt. Adjust type and extension as appropriate.
		gphoto2pp::CameraFileWrapper cameraFileWrapper;
		gphoto2pp::helper::capture(m_cameraWrapper, cameraFileWrapper, false);
		std::cout << "Captured" << std::endl << std::endl;
	} catch (gphoto2pp::exceptions::gphoto2_exception& e) {
		std::cout << "GPhoto Exception Code: " << e.getResultCode() << std::endl;
		std::cout << "Exception Message: " << e.what() << std::endl;

		// Try Again
		CaptureImage();
	}
}

void CaptureUtility::TriggerCapture() {
	try {
		std::cout << "Attempting Capture" << std::endl;
		// Trigger camera capture
		m_cameraWrapper.triggerCapture();
		
		// Let I/O Finish
		std::this_thread::sleep_for(std::chrono::milliseconds(TRIGGER_DELAY));

		std::cout << "Captured" << std::endl << std::endl;
	} catch (gphoto2pp::exceptions::gphoto2_exception& e) {
		// if(e.getResultCode()  != -110) {
			std::cout << "GPhoto Exception Code: " << e.getResultCode() << std::endl;
			std::cout << "Exception Message: " << e.what() << std::endl;
		// }

		// Try Again
		TriggerCapture();
	}
}