#include "entity.hpp"

Entity::Entity(std::unique_ptr<sf::Shape> s) : _shape(std::move(s)) {}

const sf::Vector2f Entity::get_position() const { return _position; }

void Entity::set_position(const sf::Vector2f &pos) {
    _position = pos;
    _shape->setPosition(_position);
}

void Entity::move(const sf::Vector2f &pos) { _position += pos; }

void Entity::update(const float &dt) {
    // move() only changes _position: sync the shape once per frame
    _shape->setPosition(_position);
}