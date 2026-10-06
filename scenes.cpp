#include "scenes.hpp"
#include "player.hpp"
#include "game_parameters.hpp"
#include "level_system.hpp"
#include <iostream>

using param = Parameters;
using ls = LevelSystem;
using gs = GameSystem;

std::shared_ptr<Scene> Scenes::maze;
std::shared_ptr<Scene> Scenes::end;

// ---------- MazeScene ----------

void MazeScene::update(const float &dt) {
    // the player reached the end tile
    if (ls::get_tile_at(_entities[0]->get_position()) == ls::END) {
        if (_file_path == std::string(param::maze_1)) {
            // first maze done: load the second one
            _file_path = param::maze_2;
            reset();
        } else {
            // last maze done: switch to the ending screen
            unload();
            gs::set_active_scene(Scenes::end);
        }
        return;
    }
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

    // start position is the top-left corner of the start tile: move to its centre
    const float half_tile = ls::get_tile_size() / 2.f;
    _entities[0]->set_position(ls::get_start_position() + sf::Vector2f(half_tile, half_tile));
}

void MazeScene::set_file_path(const std::string &file_path) {
    _file_path = file_path;
}

// ---------- EndScene ----------

void EndScene::load() {
    if (!font.loadFromFile(param::font_path)) {
        std::cerr << "Failed to load font: " << param::font_path << std::endl;
    }
    win_text.setFont(font);
    win_text.setString(param::end_text);
    win_text.setCharacterSize(param::end_text_size);
    win_text.setFillColor(sf::Color::White);

    // origin in the middle of the text, then put it in the middle of the window
    const sf::FloatRect bounds = win_text.getLocalBounds();
    win_text.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
    win_text.setPosition(param::game_width / 2.f, param::game_height / 2.f);
}

void EndScene::render(sf::RenderWindow &window) {
    Scene::render(window);
    window.draw(win_text);
}