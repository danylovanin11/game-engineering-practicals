#pragma once
#include <SFML/Graphics.hpp>

// Abstract base class for everything that flies: invaders and the player
class Ship : public sf::Sprite {
public:
    Ship();
    // copy constructor
    Ship(const Ship &s);
    // constructor that takes the sprite's rectangle in the sheet
    Ship(sf::IntRect ir);
    // pure virtual destructor: makes this an abstract class
    virtual ~Ship() = 0;
    // virtual so it can be overridden, but not pure virtual
    virtual void update(const float &dt);

protected:
    // which tile of the sprite-sheet this ship uses
    sf::IntRect _sprite;
};

class Invader : public Ship {
public:
    Invader();
    Invader(const Invader &inv);
    Invader(sf::IntRect ir, sf::Vector2f pos);
    void update(const float &dt) override;
};