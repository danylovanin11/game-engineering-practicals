#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <vector>
#include "entity.hpp"

// A scene is a list of entities plus the logic of one screen of the game
class Scene {
public:
    Scene() = default;
    virtual ~Scene() = default;

    virtual void update(const float &dt);
    virtual void render(sf::RenderWindow &window);
    virtual void load() = 0;
    virtual void unload();
    std::vector<std::shared_ptr<Entity>> &get_entities() { return _entities; }

protected:
    std::vector<std::shared_ptr<Entity>> _entities;
};

// Runs the window and the game loop; only static members, never instantiated
class GameSystem {
public:
    GameSystem() = delete;

    static void start(unsigned int width, unsigned int height,
                      const std::string &name, const float &time_step);
    static void clean();
    static void reset();
    static void set_active_scene(const std::shared_ptr<Scene> &act_sc);

private:
    static void _init();
    static void _update(const float &dt);
    static void _render(sf::RenderWindow &window);
    static std::shared_ptr<Scene> _active_scene;
};