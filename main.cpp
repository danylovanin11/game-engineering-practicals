#include <SFML/Graphics.hpp>
#include "game_parameters.hpp"
#include "game_system.hpp"

using param = Parameters;
using gs = GameSystem;

int main() {
    sf::RenderWindow window(sf::VideoMode(param::game_width, param::game_height), "Space Invaders");
    window.setVerticalSyncEnabled(true);

    gs::init();

    sf::Clock clock;

    while (window.isOpen()) {
        const float dt = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::Black);
        gs::update(dt);
        gs::render(window);
        window.display();
    }

    gs::clean();
    return 0;
}