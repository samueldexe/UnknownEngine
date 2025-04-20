
add_library(graphics STATIC
    renderer/RenderSystem.cpp
    renderer/Shader.cpp
    window/Window.cpp
)

target_include_directories(graphics
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/..  # Expose engine/ to access other submodules
        ${CMAKE_CURRENT_SOURCE_DIR}/../../
)

target_link_libraries(graphics PRIVATE glad glfw opengl32)