cmake_minimum_required(VERSION 3.5)
project(ballistic_fit)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Ceres REQUIRED)
# Eigen 通常被 Ceres 间接依赖，但如果需要可以显式查找：
find_package(Eigen3 REQUIRED)

add_executable(ballistic_fit main.cpp)
target_link_libraries(ballistic_fit PRIVATE ${CERES_LIBRARIES} Eigen3::Eigen)
# 若 Ceres 提供的是 ceres::ceres target, 可替换为:
# target_link_libraries(ballistic_fit PRIVATE ceres)
