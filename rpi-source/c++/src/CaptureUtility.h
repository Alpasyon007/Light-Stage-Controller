#pragma once
#include <gphoto2/gphoto2.h>
#include <gphoto2pp/camera_wrapper.hpp>
#include <gphoto2pp/camera_file_wrapper.hpp>
#include <gphoto2pp/helper_camera_wrapper.hpp>	

#include <gphoto2pp/camera_capture_type_wrapper.hpp>
#include <gphoto2pp/exceptions.hpp>

#include <gphoto2pp/window_widget.hpp>
#include <gphoto2pp/toggle_widget.hpp>
#include <gphoto2pp/radio_widget.hpp>

class CaptureUtility {
public:
	CaptureUtility();

	void CaptureToSD(bool captureToSD);
	void CaptureImage();
	void TriggerCapture();
private:
	gphoto2pp::CameraWrapper m_cameraWrapper;
};