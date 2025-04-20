
add_library(core STATIC
    Engine.cpp
)

target_include_directories(core
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/..  # Expose engine/ to access other submodules
        ${CMAKE_CURRENT_SOURCE_DIR}/../../ 
)

target_link_libraries(core PRIVATE glad glfw opengl32)