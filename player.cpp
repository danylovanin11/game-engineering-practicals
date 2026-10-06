#include "player.hpp"
#include "game_parameters.hpp"
#include "level_system.hpp"

using param = Parameters;
using ls = LevelSystem;

namespace {
// true if the circle at pos (centre) with this radius doesn't touch a wall:
// we check its four extreme points (left, right, top, bottom)
bool valid_move(const sf::Vector2f &pos, float radius) {
    return ls::get_tile_at(pos + sf::Vector2f(-radius, 0.f)) != ls::WALL &&
           ls::get_tile_at(pos + sf::Vector2f(radius, 0.f)) != ls::WALL &&
           ls::get_tile_at(pos + sf::Vector2f(0.f, -radius)) != ls::WALL &&
           ls::get_tile_at(pos + sf::Vector2f(0.f, radius)) != ls::WALL;
}
}

Player::Player() : Entity(std::make_unique<sf::CircleShape>(_radius)) {
    _shape->setFillColor(sf::Color::Magenta);
    // origin in the centre of the circle
    _shape->setOrigin(sf::Vector2f(_radius, _radius));
}

void Player::update(const float &dt) {
    // move in four directions based on keys; two keys at once = diagonal
    sf::Vector2f direction(0.f, 0.f);
    if (sf::Keyboard::isKeyPressed(param::key_up)) {
        direction.y--;
    }
    if (sf::Keyboard::isKeyPressed(param::key_down)) {
        direction.y++;
    }
    if (sf::Keyboard::isKeyPressed(param::key_left)) {
        direction.x--;
    }
    if (sf::Keyboard::isKeyPressed(param::key_right)) {
        direction.x++;
    }
    const sf::Vector2f step = direction * _speed * dt;

    // x and y are checked separately, so the player slides along walls
    if (valid_move(get_position() + sf::Vector2f(step.x, 0.f), _radius)) {
        move(sf::Vector2f(step.x, 0.f));
    }
    if (valid_move(get_position() + sf::Vector2f(0.f, step.y), _radius)) {
        move(sf::Vector2f(0.f, step.y));
    }

    Entity::update(dt);
}

void Player::render(sf::RenderWindow &window) const {
    window.draw(*_shape);
}