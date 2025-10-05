cmake_minimum_required(VERSION 3.14)
project(UnknownEngine)

set(CMAKE_CXX_STANDARD 17)

add_executable(UnknownEngine src/main.cpp)

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

# Add glad
add_library(glad STATIC thirdparty/glad/src/glad.c) 
target_include_directories(glad PUBLIC thirdparty/glad/include)
target_link_libraries(UnknownEngine PRIVATE glad)

# Add glfw
target_link_libraries(UnknownEngine PRIVATE glfw)

# Add assimp
add_library(assimp STATIC IMPORTED)
set_target_properties(assimp PROPERTIES IMPORTED_LOCATION thirdparty/assimp/lib/libassimp.a)
target_include_directories(assimp INTERFACE thirdparty/assimp/include)
target_link_libraries(UnknownEngine PRIVATE assimp) 

# Add stb_image 
add_library(stb STATIC thirdparty/stb/src/stb_image.cpp)
target_include_directories(stb PUBLIC thirdparty/stb/include)
target_link_libraries(UnknownEngine PRIVATE stb)

# Add glm header library
target_include_directories(UnknownEngine PRIVATE thirdparty/)
