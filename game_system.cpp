#include "game_system.hpp"
#include "game_parameters.hpp"
#include <iostream>

using param = Parameters;

// static members declared in the header must be defined in exactly one .cpp
sf::Texture GameSystem::spritesheet;
std::vector<std::shared_ptr<Ship>> GameSystem::ships;

void GameSystem::init() {
    // load the whole sprite-sheet once
    if (!spritesheet.loadFromFile("res/img/invaders_sheet.png")) {
        std::cerr << "Failed to load spritesheet!" << std::endl;
    }

    // shared invader state: start moving right at the initial speed
    Invader::direction = true;
    Invader::speed = param::invader_speed;

    // grid of invaders: each row uses a different sprite of the sheet
    for (int r = 0; r < param::rows; ++r) {
        sf::IntRect rect(sf::Vector2i(r * param::sprite_size, 0),
                         sf::Vector2i(param::sprite_size, param::sprite_size));
        for (int c = 0; c < param::columns; ++c) {
            sf::Vector2f position(param::invader_start_x + c * param::invader_spacing,
                                  param::invader_start_y + r * param::invader_spacing);
            std::shared_ptr<Invader> inv = std::make_shared<Invader>(rect, position);
            ships.push_back(inv);
        }
    }
}

void GameSystem::clean() {
    // free the memory of every ship
    for (std::shared_ptr<Ship> &ship : ships) {
        ship.reset();
    }
    ships.clear();
}

void GameSystem::update(const float &dt) {
    // polymorphism: each ship runs its own update()
    for (std::shared_ptr<Ship> &s : ships) {
        s->update(dt);
    }
}

void GameSystem::render(sf::RenderWindow &window) {
    // ships inherit from sf::Sprite, so SFML can draw them directly
    for (const std::shared_ptr<Ship> &s : ships) {
        window.draw(*(s.get()));
    }
}