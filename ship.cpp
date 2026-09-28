#include "ship.hpp"
#include "game_system.hpp"
#include "game_parameters.hpp"

using param = Parameters;
using gs = GameSystem;

// ---------- Ship ----------

Ship::Ship() {}

// copy the sf::Sprite part too, otherwise texture and position are lost
Ship::Ship(const Ship &s) : sf::Sprite(s), _sprite(s._sprite) {}

Ship::Ship(sf::IntRect ir) : sf::Sprite() {
    _sprite = ir;
    setTexture(gs::spritesheet);
    setTextureRect(_sprite);
}

// pure virtual destructor still needs a definition
Ship::~Ship() = default;

void Ship::update(const float &dt) {}

// ---------- Invader ----------

Invader::Invader() : Ship() {}

Invader::Invader(const Invader &inv) : Ship(inv) {}

Invader::Invader(sf::IntRect ir, sf::Vector2f pos) : Ship(ir) {
    // origin in the middle of the sprite
    setOrigin(sf::Vector2f(param::sprite_size / 2.f, param::sprite_size / 2.f));
    setPosition(pos);
}

void Invader::update(const float &dt) {
    Ship::update(dt);
}