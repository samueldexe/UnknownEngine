
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

message(STATUS "GLAD include path: ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glad/include")

# Engine Submodules
add_subdirectory(core)
add_subdirectory(graphics) 
add_subdirectory(ecs)
add_subdirectory(resources)

add_library(UnknownEngine INTERFACE)

target_include_directories(UnknownEngine INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/../include  # For public headers 
     ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glad/include  # Include GLAD headers
)

target_link_libraries(UnknownEngine INTERFACE
    core
    graphics
    ecs
    resources
)