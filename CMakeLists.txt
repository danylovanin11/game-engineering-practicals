cmake_minimum_required(VERSION 3.10)
project(tile_maze)
# Require modern C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#### Setup Directories ####
# Main output directory
SET(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
# Output all DLLs from all libs into main build folder
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})

#### Add External Dependencies ####
add_subdirectory("lib/SFML")
set(SFML_INCS "lib/SFML/include")
link_directories("${CMAKE_BINARY_DIR}/lib/SFML/lib")

#### Copy resources next to the executable ####
add_custom_target(copy_resources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/res"
        "${OUTPUT_DIRECTORY}/res"
)

#### Practical 4: Tile Maze ####
add_executable(tile_maze main.cpp game_system.cpp entity.cpp player.cpp scenes.cpp)
target_include_directories(tile_maze PRIVATE ${SFML_INCS})
target_link_libraries(tile_maze sfml-graphics)
set_target_properties(tile_maze PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY ${OUTPUT_DIRECTORY})
add_dependencies(tile_maze copy_resources)