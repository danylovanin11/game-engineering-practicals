#include "scenes.hpp"
#include "player.hpp"
#include "game_parameters.hpp"

using param = Parameters;

std::shared_ptr<Scene> Scenes::maze;

void MazeScene::update(const float &dt) {
    Scene::update(dt);
}

void MazeScene::render(sf::RenderWindow &window) {
    Scene::render(window);
}

void MazeScene::load() {
    std::shared_ptr<Entity> player = std::make_shared<Player>();
    _entities.push_back(player);
    reset();
}

void MazeScene::reset() {
    // the player is always the first entity;
    // for now it starts in the centre, later it will start on the 's' tile of the maze
    _entities[0]->set_position(sf::Vector2f(param::game_width / 2.f, param::game_height / 2.f));
}

void MazeScene::set_file_path(const std::string &file_path) {
    _file_path = file_path;
}