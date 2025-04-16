
# GLFW setup
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)
add_subdirectory(thirdparty/glfw)

# GLAD
add_library(glad STATIC thirdparty/glad/src/glad.c)
target_include_directories(glad PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glad/include
)

# Engine library
add_library(UnknownEngine STATIC
    core/Engine.cpp
    input_system/InputSystem.cpp
    window/Window.cpp
)

target_include_directories(UnknownEngine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../include  # For public headers
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}  # For private headers
    ${GLFW_INCLUDE_DIRS}
)

target_link_libraries(UnknownEngine PRIVATE
    glad
    glfw
    opengl32
)