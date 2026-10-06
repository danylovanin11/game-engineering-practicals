#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

// Abstract base class for everything in a scene; it owns an sf::Shape
class Entity {
public:
    Entity(std::unique_ptr<sf::Shape> shp);
    Entity() = delete;
    virtual ~Entity() = default;

    virtual void update(const float &dt);
    virtual void render(sf::RenderWindow &window) const = 0;

    const sf::Vector2f get_position() const;
    void set_position(const sf::Vector2f &pos);
    void move(const sf::Vector2f &pos);

protected:
    std::unique_ptr<sf::Shape> _shape;
    sf::Vector2f _position;
};