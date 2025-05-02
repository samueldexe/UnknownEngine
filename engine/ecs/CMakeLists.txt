
add_library(ecs STATIC
    component/ComponentManager.cpp
    component/default_components/MeshComponent.cpp

    entity/EntityManager.cpp
    
    system/SystemManager.cpp
    system/default_systems/input_system/InputSystem.cpp
 )

target_include_directories(ecs
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/..  # Expose engine/ to access other submodules
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../../ #Expore resources/ to files in the include folder
)

target_link_libraries(ecs  PUBLIC glad glfw opengl32)