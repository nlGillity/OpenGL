cmake_minimum_required(VERSION 3.10)
project(App)

add_executable(App main.cpp)

add_subdirectory(libs/glfw)
add_subdirectory(libs/glad)
target_link_libraries(App glfw glad)