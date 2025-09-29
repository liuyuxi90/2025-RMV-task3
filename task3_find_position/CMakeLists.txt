cmake_minimum_required(VERSION 3.10)
project(ball_tracking)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)

add_executable(ball_tracking main.cpp)
target_link_libraries(ball_tracking PRIVATE ${OpenCV_LIBS})
