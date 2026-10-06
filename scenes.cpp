#include "scenes.hpp"
#include "player.hpp"
#include "game_parameters.hpp"
#include "level_system.hpp"
#include <iostream>

using param = Parameters;
using ls = LevelSystem;

std::shared_ptr<Scene> Scenes::maze;

void MazeScene::update(const float &dt) {
    Scene::update(dt);
}

void MazeScene::render(sf::RenderWindow &window) {
    // the maze first, so the player is drawn on top of it
    ls::render(window);
    Scene::render(window);
}

void MazeScene::load() {
    std::shared_ptr<Entity> player = std::make_shared<Player>();
    _entities.push_back(player);
    reset();
}

void MazeScene::reset() {
    ls::load_level(_file_path, param::tile_size);

    // print the maze as tile numbers to check the loading
    for (int y = 0; y < ls::get_height(); ++y) {
        for (int x = 0; x < ls::get_width(); ++x) {
            std::cout << ls::get_tile({x, y});
        }
        std::cout << std::endl;
    }

    // still in the centre for now; on stage B it moves to the start tile
    _entities[0]->set_position(sf::Vector2f(param::game_width / 2.f, param::game_height / 2.f));
}

void MazeScene::set_file_path(const std::string &file_path) {
    _file_path = file_path;
}