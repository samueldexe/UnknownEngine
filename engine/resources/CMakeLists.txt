
add_library(resources STATIC
    mesh/Mesh.cpp
    mesh/MeshManager.cpp
)

target_include_directories(resources
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/..  # Expose engine/ to access other submodules
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../../ #Expore resources/ to files in the include folder
)

target_link_libraries(resources  PUBLIC glad glfw opengl32)