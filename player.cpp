#include "player.hpp"
#include "game_parameters.hpp"

using param = Parameters;

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
    move(direction * _speed * dt);

    Entity::update(dt);
}

void Player::render(sf::RenderWindow &window) const {
    window.draw(*_shape);
}