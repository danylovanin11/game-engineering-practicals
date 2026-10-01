#pragma once
#include <SFML/Graphics.hpp>
#include "game_parameters.hpp"

// All bullets live in a static pool: nothing outside this class ever creates one
class Bullet : public sf::Sprite {
public:
    // updates all bullets (calls _update() on every bullet of the pool)
    static void update(const float &dt);
    // renders all bullets of the pool
    static void render(sf::RenderWindow &window);
    // takes the next bullet of the pool and fires it
    static void fire(const sf::Vector2f &pos, const bool mode);
    // puts every bullet off-screen and gives it the sprite-sheet
    static void init();
    ~Bullet() = default;

protected:
    Bullet();
    // true = player bullet (goes up), false = invader bullet (goes down)
    bool _mode = false;
    // moves this bullet; called by the static update()
    void _update(const float &dt);

    // index of the last fired bullet, wraps from 255 back to 0 on its own
    static unsigned char _bullet_pointer;
    static Bullet _bullets[Parameters::bullet_pool_size];
};