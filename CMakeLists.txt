cmake_minimum_required(VERSION 3.10)
project(App)

add_executable(App main.cpp shader.cpp primitives.cpp)

add_subdirectory(libs/glfw)
add_subdirectory(libs/glad)
add_subdirectory(libs/glm)
target_link_libraries(App glfw glad glm::glm)