#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "ship.hpp"

// Holds the game state and the main system functions (instead of globals)
struct GameSystem {
    // the sprite-sheet shared by every sprite in the game
    static sf::Texture spritesheet;
    // every ship in the game (invaders now, the player later)
    static std::vector<std::shared_ptr<Ship>> ships;

    // game system functions
    static void init();
    static void clean();
    static void update(const float &dt);
    static void render(sf::RenderWindow &window);
};