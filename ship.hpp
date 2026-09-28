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
    // drops the ship down; does nothing by default (the player ignores it)
    virtual void move_down();

protected:
    // which tile of the sprite-sheet this ship uses
    sf::IntRect _sprite;
};

class Invader : public Ship {
public:
    // shared by ALL invaders: true = moving right, false = moving left
    static bool direction;
    // shared by ALL invaders: current horizontal speed
    static float speed;

    Invader();
    Invader(const Invader &inv);
    Invader(sf::IntRect ir, sf::Vector2f pos);
    void update(const float &dt) override;
    void move_down() override;
};

class Player : public Ship {
public:
    // no copy constructor needed: Player has no member data of its own yet
    Player();
    void update(const float &dt) override;
};