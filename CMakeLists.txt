cmake_minimum_required(VERSION 3.15)

# Project name
project(SoftRender)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)

# Source files
file(GLOB SOURCES
    src/*.cpp
)

# Add executable
add_executable(${PROJECT_NAME} ${SOURCES})
