cmake_minimum_required(VERSION 3.30)
project(pwr_racing)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(point)
add_subdirectory(utils)
add_subdirectory(convex_hull)

add_executable(pwr_racing src/main.cpp)

target_link_libraries(pwr_racing PRIVATE utils convex_hull)
