#include <memory>
#include "game_parameters.hpp"
#include "game_system.hpp"
#include "scenes.hpp"

using param = Parameters;

int main() {
    Scenes::maze = std::make_shared<MazeScene>();
    std::static_pointer_cast<MazeScene>(Scenes::maze)->set_file_path(param::maze_1);
    Scenes::maze->load();

    // without this Scenes::end is empty and switching to it crashes (segfault)
    Scenes::end = std::make_shared<EndScene>();
    Scenes::end->load();

    GameSystem::set_active_scene(Scenes::maze);
    GameSystem::start(param::game_width, param::game_height, "Tile Maze", param::time_step);
    return 0;
}