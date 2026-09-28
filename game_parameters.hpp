#pragma once

// All the game parameters in one place: no hard coded values anywhere else
struct Parameters {
    static constexpr int game_width = 800;
    static constexpr int game_height = 600;
    static constexpr int sprite_size = 32;

    // invaders movement
    static constexpr float invader_speed = 50.f;  // initial horizontal speed (px/s)
    static constexpr float invader_acc = 10.f;    // speed gained at each edge bounce
    static constexpr float invader_drop = 24.f;   // how far invaders drop at each edge
};