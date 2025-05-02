
add_library(core STATIC
    Engine.cpp
)

target_include_directories(core
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/..  # Expose engine/ to access other submodules
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../../  #Expore resources/ to files in the include folder
)

target_link_libraries(core PUBLIC glad glfw opengl32)