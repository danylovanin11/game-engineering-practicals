cmake_minimum_required(VERSION 3.10)
project(space_invaders)
# Require modern C++
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#### Setup Directories ####
#Main output directory
SET(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
# Ouput all DLLs from all libs into main build folder
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})

#### Add External Dependencies ####
set(CMAKE_WARN_DEPRECATED OFF CACHE BOOL "" FORCE)
add_subdirectory("lib/SFML")
set(SFML_INCS "lib/SFML/include")
link_directories("${CMAKE_BINARY_DIR}/lib/SFML/lib")

#### Copy resources next to the executable ####
add_custom_target(copy_resources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/res"
        "${OUTPUT_DIRECTORY}/res"
)



#### Practical 3 ####
add_executable(space_invaders main.cpp game_system.cpp ship.cpp bullet.cpp)
target_include_directories(space_invaders PRIVATE ${SFML_INCS})
target_link_libraries(space_invaders sfml-graphics)
set_target_properties(space_invaders PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY ${OUTPUT_DIRECTORY})
add_dependencies(space_invaders copy_resources)