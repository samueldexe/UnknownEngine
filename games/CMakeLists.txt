
cmake_minimum_required(VERSION 3.15)
project(Sandbox)

# Create the executable
add_executable(Sandbox main.cpp)

# Link the engine library
target_link_libraries(Sandbox PRIVATE UnknownEngine)

# Add the public include directory 
target_include_directories(Sandbox PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../include  
)