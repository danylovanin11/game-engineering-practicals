#include "game_system.hpp"

// static members declared in the header must be defined in exactly one .cpp
std::shared_ptr<Scene> GameSystem::_active_scene;

// ---------- Scene ----------

void Scene::update(const float &dt) {
    for (std::shared_ptr<Entity> &ent : _entities) {
        ent->update(dt);
    }
}

void Scene::render(sf::RenderWindow &window) {
    for (std::shared_ptr<Entity> &ent : _entities) {
        ent->render(window);
    }
}

void Scene::unload() {
    _entities.clear();
}

// ---------- GameSystem ----------

void GameSystem::start(unsigned int width, unsigned int height,
                       const std::string &name, const float &time_step) {
    sf::RenderWindow window(sf::VideoMode(width, height), name);
    window.setVerticalSyncEnabled(true);
    _init();

    sf::Clock clock;
    sf::Event event;
    while (window.isOpen()) {
        const float dt = clock.restart().asSeconds();

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                clean();
                return;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
        }

        window.clear();
        _update(dt);
        _render(window);
        sf::sleep(sf::seconds(time_step));
        // wait for vsync
        window.display();
    }
    clean();
}

void GameSystem::clean() {
    if (_active_scene) {
        _active_scene->unload();
    }
    _active_scene.reset();
}

void GameSystem::reset() {
    // reload the active scene from scratch
    if (_active_scene) {
        _active_scene->unload();
        _active_scene->load();
    }
}

void GameSystem::set_active_scene(const std::shared_ptr<Scene> &act_sc) {
    _active_scene = act_sc;
}

void GameSystem::_init() {
    // nothing to set up yet: each scene loads its own content
}

void GameSystem::_update(const float &dt) {
    if (_active_scene) {
        _active_scene->update(dt);
    }
}

void GameSystem::_render(sf::RenderWindow &window) {
    if (_active_scene) {
        _active_scene->render(window);
    }
}