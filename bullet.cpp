#include "bullet.hpp"
#include "game_system.hpp"

using param = Parameters;
using gs = GameSystem;

// static members must be defined in exactly one .cpp
unsigned char Bullet::_bullet_pointer = 0;
Bullet Bullet::_bullets[param::bullet_pool_size];

Bullet::Bullet() {}

void Bullet::update(const float &dt) {
    for (Bullet &bullet : _bullets) {
        bullet._update(dt);
    }
}

void Bullet::render(sf::RenderWindow &window) {
    for (const Bullet &bullet : _bullets) {
        window.draw(bullet);
    }
}

void Bullet::fire(const sf::Vector2f &pos, const bool mode) {
    Bullet &bullet = _bullets[++_bullet_pointer];
    if (mode) {
        // player bullet: white, 2nd tile of the second row
        bullet.setTextureRect(sf::IntRect(sf::Vector2i(param::sprite_size, param::sprite_size),
                                          sf::Vector2i(param::sprite_size, param::sprite_size)));
    } else {
        // invader bullet: green, 3rd tile of the second row
        bullet.setTextureRect(sf::IntRect(sf::Vector2i(param::sprite_size * 2, param::sprite_size),
                                          sf::Vector2i(param::sprite_size, param::sprite_size)));
    }
    bullet.setPosition(pos);
    bullet._mode = mode;
}

void Bullet::init() {
    for (Bullet &bullet : _bullets) {
        bullet.setTexture(gs::spritesheet);
        // give it a real tile right away, so an unused bullet never shows the whole sheet
        bullet.setTextureRect(sf::IntRect(sf::Vector2i(param::sprite_size, param::sprite_size),
                                          sf::Vector2i(param::sprite_size, param::sprite_size)));
        bullet.setOrigin(sf::Vector2f(param::sprite_size / 2.f, param::sprite_size / 2.f));
        bullet.setPosition(sf::Vector2f(-100.f, -100.f));
    }
}

void Bullet::_update(const float &dt) {
    if (getPosition().y < -param::sprite_size ||
        getPosition().y > param::game_height + param::sprite_size) {
        // off-screen: inactive, do nothing
        return;
    }
    // player bullets go up, invader bullets go down
    move(sf::Vector2f(0.f, dt * param::bullet_speed * (_mode ? -1.0f : 1.0f)));
    // collisions come in the next step
}