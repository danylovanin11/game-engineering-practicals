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
    // true once the ship has been hit
    bool is_exploded() const;
    // true once the explosion has completely faded out
    bool is_faded() const;
    // turns the ship into the explosion sprite
    virtual void explode();

protected:
    // which tile of the sprite-sheet this ship uses
    sf::IntRect _sprite;
    bool _exploded = false;
    // time left before the explosion has faded out
    float _explode_time = 0.f;
};

class Invader : public Ship {
public:
    // shared by ALL invaders: true = moving right, false = moving left
    static bool direction;
    // shared by ALL invaders: current horizontal speed
    static float speed;
    // shared by ALL invaders: time left before any invader may fire again
    static float fire_time;

    // updates the state shared by all invaders, called once per frame
    static void update_fire_timer(const float &dt);

    Invader();
    Invader(const Invader &inv);
    Invader(sf::IntRect ir, sf::Vector2f pos);
    void update(const float &dt) override;
    void move_down() override;
    void explode() override;
};

class Player : public Ship {
public:
    // no copy constructor needed: Player has no member data of its own yet
    Player();
    void update(const float &dt) override;
};