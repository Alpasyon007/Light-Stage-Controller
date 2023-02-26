# CMake Bulid File
#
# CMake Version
cmake_minimum_required(VERSION 3.10)

# Compiler Settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set Variables
set(SOURCE_DIR src)

# Set the project name
project(listpi)

add_executable(
	listpi 
	${SOURCE_DIR}/listpi.cpp
	${SOURCE_DIR}/StepperMotorController.cpp
	${SOURCE_DIR}/StepperMotorController.h
	${SOURCE_DIR}/Serial.cpp
	${SOURCE_DIR}/Serial.h
	${SOURCE_DIR}/CaptureUtility.h
	${SOURCE_DIR}/CaptureUtility.cpp
	${SOURCE_DIR}/LEDController.h
	${SOURCE_DIR}/LEDController.cpp
)

target_include_directories(listpi PRIVATE ${SOURCE_DIR})

target_link_libraries(listpi PUBLIC pigpio gphoto2_port gphoto2 gphoto2pp)