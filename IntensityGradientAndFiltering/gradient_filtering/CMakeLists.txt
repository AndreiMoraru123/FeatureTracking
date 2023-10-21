cmake_minimum_required(VERSION 3.23)

set(CMAKE_CXX_STANDARD 17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(camera_fusion)

set( OpenCV_DIR "D:\\opencv\\build\\")
find_package(OpenCV 4.3 REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIBRARY_DIRS})
add_definitions(${OpenCV_DEFINITIONS})

# Executable for create matrix exercise
add_executable (gaussian_smoothing src/gaussian_smoothing.cpp)
target_link_libraries (gaussian_smoothing ${OpenCV_LIBRARIES})

add_executable(gradient_sobel src/gradient_sobel.cpp)
target_link_libraries(gradient_sobel ${OpenCV_LIBRARIES})

add_executable(magnitude_sobel src/magnitude_sobel.cpp)
target_link_libraries(magnitude_sobel ${OpenCV_LIBRARIES})