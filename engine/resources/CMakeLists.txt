
add_library(resources STATIC
    mesh/Mesh.cpp
    mesh/MeshManager.cpp
)

target_include_directories(resources
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/..  # Expose engine/ to access other submodules
        ${CMAKE_CURRENT_SOURCE_DIR}/../../
)

target_link_libraries(resources PRIVATE glad glfw opengl32)