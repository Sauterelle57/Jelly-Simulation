cmake_minimum_required(VERSION 3.5)
set(CMAKE_BUILD_TYPE "Debug")
project(JellySimulation)

list(PREPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Libigl
include(libigl)

# Enable the target igl::glfw
igl_include(glfw)
igl_include(imgui)

# Add your project files
file(GLOB SRC_FILES src/*.cpp)
add_executable(${PROJECT_NAME} ${SRC_FILES})

# Link igl (and the glfw module) to your project
target_link_libraries(${PROJECT_NAME} PUBLIC
  igl::glfw
  igl::imgui
)

add_custom_command(
  TARGET ${PROJECT_NAME} PRE_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_CURRENT_SOURCE_DIR}/models
  ${CMAKE_CURRENT_BINARY_DIR}
)
