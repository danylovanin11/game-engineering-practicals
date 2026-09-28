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

// ---------- Player ----------

// the player cannon is the 6th tile (index 5) of the second row of the sheet
Player::Player()
    : Ship(sf::IntRect(sf::Vector2i(param::sprite_size * 5, param::sprite_size),
                       sf::Vector2i(param::sprite_size, param::sprite_size))) {
    setOrigin(sf::Vector2f(param::sprite_size / 2.f, param::sprite_size / 2.f));
    // centred horizontally, one sprite above the bottom of the window
    setPosition(sf::Vector2f(param::game_width / 2.f,
                             param::game_height - static_cast<float>(param::sprite_size)));
}

void Player::update(const float &dt) {
    Ship::update(dt);

    // move left / right, same idea as the paddles in Pong
    float direction = 0.f;
    if (sf::Keyboard::isKeyPressed(param::key_left)) {
        direction--;
    }
    if (sf::Keyboard::isKeyPressed(param::key_right)) {
        direction++;
    }
    move(sf::Vector2f(direction * param::player_speed * dt, 0.f));

    // keep the player inside the window
    const float half_size = param::sprite_size / 2.f;
    if (getPosition().x < half_size) {
        setPosition(sf::Vector2f(half_size, getPosition().y));
    } else if (getPosition().x > param::game_width - half_size) {
        setPosition(sf::Vector2f(param::game_width - half_size, getPosition().y));
    }
}