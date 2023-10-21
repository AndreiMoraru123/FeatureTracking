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
add_executable (show_lidar src/show_lidar_top_view.cpp)
target_link_libraries(show_lidar ${OpenCV_LIBRARIES})

add_executable (project src/project_lidar_to_camera.cpp)
target_link_libraries(project ${OpenCV_LIBRARIES})