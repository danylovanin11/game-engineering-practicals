#include <SFML/Graphics.hpp>
#include <iostream>

// window parameters
const unsigned int gameWidth = 800;
const unsigned int gameHeight = 600;


sf::Texture spritesheet;
sf::Sprite invader;

void init() {
  if (!spritesheet.loadFromFile("res/img/invaders_sheet.png")) {
    std::cerr << "Failed to load spritesheet!" << std::endl;
  }
  invader.setTexture(spritesheet);
  invader.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(32, 32)));
}

void update(float dt) {
    // nothing to update yet
}

void render(sf::RenderWindow &window) {
    window.draw(invader);
}

int main() {
    sf::RenderWindow window(sf::VideoMode({gameWidth, gameHeight}), "Space Invaders");
    window.setVerticalSyncEnabled(true);

    init();

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
        update(dt);
        render(window);
        window.display();
    }

    return 0;
}