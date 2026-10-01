#pragma once
#include <SFML/Window/Keyboard.hpp>

// All the game parameters in one place: no hard coded values anywhere else
struct Parameters {
    static constexpr int game_width = 800;
    static constexpr int game_height = 600;
    static constexpr int sprite_size = 32;

    // invaders movement
    static constexpr float invader_speed = 50.f;    // initial horizontal speed (px/s)
    static constexpr float invader_acc = 10.f;      // speed gained at each edge bounce
    static constexpr float invader_drop = 24.f;     // how far invaders drop at each edge
    static constexpr float invader_kill_acc = 2.f;  // speed gained each time an invader is killed

    // invaders shooting
    static constexpr float invader_fire_cooldown = 1.f; // minimum seconds between two invader shots
    static constexpr int invader_fire_random = 200;     // extra random delay, in 1/100 s (0 to 2 s)
    static constexpr int invader_fire_chance = 100;     // each invader fires with 1 chance in this per frame

    // invaders grid
    static constexpr int rows = 5;                  // one sprite type per row
    static constexpr int columns = 12;
    static constexpr float invader_spacing = 40.f;  // distance between invader centres
    static constexpr float invader_start_x = 100.f; // centre of the top-left invader
    static constexpr float invader_start_y = 64.f;

    // player
    static constexpr float player_speed = 200.f;    // horizontal speed (px/s)
    static constexpr sf::Keyboard::Key key_left = sf::Keyboard::Left;
    static constexpr sf::Keyboard::Key key_right = sf::Keyboard::Right;
    static constexpr sf::Keyboard::Key key_fire = sf::Keyboard::Space;
    static constexpr float player_fire_cooldown = 0.7f; // seconds between two player shots

    // bullets
    static constexpr int bullet_pool_size = 256;  // must stay 256: the pool index is an unsigned char
    static constexpr float bullet_speed = 200.f;  // vertical speed (px/s)

    // explosions
    static constexpr float explosion_time = 1.f;  // seconds for an explosion to fade out
};