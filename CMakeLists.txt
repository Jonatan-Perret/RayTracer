cmake_minimum_required(VERSION 3.27)
project(RayTracing)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(RayTracing main.cpp
        RayTracer.cpp
        RayTracer.h
)

cmake_minimum_required(VERSION 3.10)

# Set your project name
project(RayTracing)

# Locate SDL2 package (Adjust the path if necessary)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

# Link the SDL2 libraries
target_link_libraries(RayTracing ${SDL2_LIBRARIES})



