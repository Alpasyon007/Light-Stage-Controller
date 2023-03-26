# CMake Bulid File
#
# CMake Version
cmake_minimum_required(VERSION 3.10)

# Compiler Settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ldl -lutil -lpthread -W")

# Set the project name
project(listpi)

add_executable(
	listpi
	${CMAKE_CURRENT_SOURCE_DIR}/src/listpi.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/StepperMotorController/StepperMotorController.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/StepperMotorController/StepperMotorController.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/Serial/Serial.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Serial/Serial.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/CaptureUtility/CaptureUtility.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/CaptureUtility/CaptureUtility.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/LEDController/LEDController.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/LEDController/LEDController.cpp

	# ImGui
	# ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imconfig.h
	# ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui.cpp
	# ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_draw.cpp
	# ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_widgets.cpp
	# ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_demo.cpp
	# ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_tables.cpp
	# ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_tables.cpp
	# ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_tables.cpp

	# ImGui DirectX 12 Backends
	# ${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_opengl3.cpp
)

target_include_directories(
	listpi
	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/src/StepperMotorController
	${CMAKE_CURRENT_SOURCE_DIR}/src/Serial
	${CMAKE_CURRENT_SOURCE_DIR}/src/CaptureUtility
	${CMAKE_CURRENT_SOURCE_DIR}/src/LEDController
	${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty

	# OpenCV
	${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/opencv/include
	${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/opencv/modules/calib3d/include
    ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/opencv/modules/core/include
    ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/opencv/modules/cudaarithm/include
    ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/opencv/modules/cudabgsegm/include
    ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/opencv/modules/cudacodec/include
    ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/opencv/modules/cudafeatures2d/include
    ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/opencv/modules/cudafilters/include
    ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/opencv/modules/cudaimgproc/include
    ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/opencv/modules/cudalegacy/include
    ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/opencv/modules/cudaobjdetect/include
    ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/opencv/modules/cudaoptflow/include
    ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/opencv/modules/cudastereo/include
    ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/opencv/modules/cudawarping/include
    ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/opencv/modules/cudev/include
    ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/opencv/modules/dnn/include
    ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/opencv/modules/features2d/include
    ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/opencv/modules/flann/include
    ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/opencv/modules/highgui/include
    ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/opencv/modules/imgcodecs/include
    ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/opencv/modules/imgproc/include
    ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/opencv/modules/ml/include
    ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/opencv/modules/objdetect/include
    ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/opencv/modules/photo/include
    ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/opencv/modules/shape/include
    ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/opencv/modules/stitching/include
    ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/opencv/modules/superres/include
    ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/opencv/modules/ts/include
    ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/opencv/modules/video/include
    ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/opencv/modules/videoio/include
    ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/opencv/modules/videostab/include
    ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/opencv/modules/viz/include
    ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/opencv/modules/world/include

	#OpenCV Contrib
	${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/opencv_contrib/modules/aruco/include

	# ${CMAKE_CURRENT_SOURCE_DIR}/NoesisGUI/Include
	# ${CMAKE_CURRENT_SOURCE_DIR}/NoesisGUI/Include/NsRender
	# ${CMAKE_CURRENT_SOURCE_DIR}/NoesisGUI/Bin/linux_arm
	# ${CMAKE_CURRENT_SOURCE_DIR}/imgui
	# ${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends
	# ${CMAKE_CURRENT_SOURCE_DIR}/glfw
)

target_link_libraries(
	listpi
	PUBLIC
	pigpio
	gphoto2_port
	gphoto2
	gphoto2pp
	# opencv_core
	# opencv_objdetect
	# opencv_calib3d
	# opencv_highgui
	# opencv_aruco
	# libNoesis
)
