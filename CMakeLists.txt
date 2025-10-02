cmake_minimum_required(VERSION 3.14)
project(UnknownEngine)

set(CMAKE_CXX_STANDARD 17)

# FetchContent for GLFW
include(FetchContent)
FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG 3.3.8
)
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)
FetchContent_MakeAvailable(glfw)

# Add GLAD 
add_library(glad STATIC thirdparty/glad/src/glad.c) 
target_include_directories(glad PUBLIC thirdparty/glad/include)

add_executable(UnknownEngine src/main.cpp src/stb_image.cpp)
target_link_libraries(UnknownEngine PRIVATE glfw glad)

# Add stb_image library
target_include_directories(UnknownEngine PRIVATE thirdparty/)

# Add glm library
target_include_directories(UnknownEngine PRIVATE thirdparty/glm)
