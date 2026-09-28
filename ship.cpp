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

// by default a ship does not move down (the player uses this version)
void Ship::move_down() {}

// ---------- Invader ----------

// static members must be defined in exactly one .cpp
bool Invader::direction;
float Invader::speed;

Invader::Invader() : Ship() {}

Invader::Invader(const Invader &inv) : Ship(inv) {}

Invader::Invader(sf::IntRect ir, sf::Vector2f pos) : Ship(ir) {
    // origin in the middle of the sprite
    setOrigin(sf::Vector2f(param::sprite_size / 2.f, param::sprite_size / 2.f));
    setPosition(pos);
}

void Invader::update(const float &dt) {
    Ship::update(dt);

    // move left or right at the shared speed
    move(sf::Vector2f(dt * (direction ? 1.0f : -1.0f) * speed, 0.0f));

    // touching an edge while heading towards it: every invader turns around and drops
    if ((direction && getPosition().x > param::game_width - param::sprite_size / 2.f) ||
        (!direction && getPosition().x < param::sprite_size / 2.f)) {
        direction = !direction;
        speed += param::invader_acc;
        for (std::shared_ptr<Ship> &ship : gs::ships) {
            ship->move_down();
        }
    }
}

void Invader::move_down() {
    move(sf::Vector2f(0.f, param::invader_drop));
}