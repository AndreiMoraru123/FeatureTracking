cmake_minimum_required(VERSION 3.23)
project(CameraVision)

set(CMAKE_CXX_STANDARD 17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

set(OpenCV_DIR "C:\\Users\\Andrei\\OpenCvPython\\build")
include_directories( "C:\\Users\\Andrei\\OpenCvPython\\opencv-4.5.2\\include" )
find_package(OpenCV 4.5 REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIBRARY_DIRS})
add_definitions(${OpenCV_DEFINITIONS})

add_subdirectory(Exercises)
add_subdirectory(TTC-lidar)
add_subdirectory(TTC-camera)
add_subdirectory(IntensityGradientAndFiltering/gradient_filtering)
add_subdirectory(HarrisCornerDetection)
add_subdirectory(detect_keypoints)
add_subdirectory(descriptor_matching)
add_subdirectory(lidar_to_camera)
add_subdirectory(Creating3DObjects)


add_executable(CameraVision main.cpp)
target_link_libraries (CameraVision ${OpenCV_LIBRARIES})