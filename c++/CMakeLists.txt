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

add_executable(listpi ${SOURCE_DIR}/listpi.cpp)

target_link_libraries(listpi pigpio)