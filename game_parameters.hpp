#pragma once
#include <SFML/Window/Keyboard.hpp>

// All the game parameters in one place: no hard coded values anywhere else
struct Parameters {
    static constexpr int game_width = 800;
    static constexpr int game_height = 600;
    static constexpr float time_step = 0.01f;   // pause at the end of each frame (s)
    static constexpr float tile_size = 100.f;   // size of one maze tile (px)

    // maze files
    static constexpr const char *maze_1 = "res/levels/maze_1.txt";
    static constexpr const char *maze_2 = "res/levels/maze_2.txt";

    // player controls
    static constexpr sf::Keyboard::Key key_up = sf::Keyboard::Up;
    static constexpr sf::Keyboard::Key key_down = sf::Keyboard::Down;
    static constexpr sf::Keyboard::Key key_left = sf::Keyboard::Left;
    static constexpr sf::Keyboard::Key key_right = sf::Keyboard::Right;

    // ending screen
    static constexpr const char *font_path = "res/fonts/RobotoMono-Regular.ttf";
    static constexpr const char *end_text = "You win!";
    static constexpr unsigned int end_text_size = 48;
};