
add_library(graphics STATIC
    renderer/RenderSystem.cpp
    renderer/Shader.cpp
    window/Window.cpp
)

target_include_directories(graphics
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/..  # Expose engine/ to access other submodules
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../../ #Expore resources/ to files in the include folder
)

target_link_libraries(graphics PUBLIC glad opengl32 glfw)