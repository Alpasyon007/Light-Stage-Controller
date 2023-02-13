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
project(captureTest)

add_executable(
	captureTest 
	${SOURCE_DIR}/captureTest.cpp
)

target_include_directories(captureTest PRIVATE ${SOURCE_DIR})

target_link_libraries(captureTest PUBLIC gphoto2_port gphoto2 gphoto2pp)