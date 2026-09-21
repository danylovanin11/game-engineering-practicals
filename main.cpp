#include <SFML/Graphics.hpp>

const sf::Keyboard::Key controls[4] = {
  sf::Keyboard::A, //player 1 up
  sf::Keyboard::Z, //player 1 down
  sf::Keyboard::Up, //player 2 UP
  sf::Keyboard::Down //player 2 down
};

//parameters 

const sf::Vector2f paddleSize(25.f, 100.f);
const float ballRadius = 10.f;
const int gameWidth = 800;
const int gameHeight = 600;
const float paddleSpeed = 400.f;
const float paddleOffsetWall = 10.f;
const float time_step = 0.017f; //60 fps

//objects of the game
sf::CircleShape ball;
sf::RectangleShape paddles[2];

void init() {
    // size and origin of paddles
    for (sf::RectangleShape &p : paddles){
      p.setSize(paddleSize);
      p.setOrigin(paddleSize / 2.f);
    }
    //size and origin of the ball
    ball.setRadius(ballRadius);
    ball.setOrigin(sf::Vector2f(ballRadius, ballRadius));
    //reset paddle position
    paddles[0].setPosition(sf::Vector2f(paddleOffsetWall + paddleSize.x / 2.f, gameHeight / 2.f));
    paddles[1].setPosition(sf::Vector2f(gameWidth - paddleOffsetWall - paddleSize.x / 2.f, gameHeight / 2.f));
    //reset ball position
    ball.setPosition(sf::Vector2f(gameWidth / 2.f, gameHeight / 2.f));
}

void update(float dt) {
    // handle paddle movement
    float direction = 0.0f;
    if (sf::Keyboard::isKeyPressed(controls[0])){
      direction--;
    }
    if (sf::Keyboard::isKeyPressed(controls[1])){
      direction++;
    }
    paddles[0].move(sf::Vector2f(0.f, direction * paddleSpeed * dt));
}

void render(sf::RenderWindow &window) {
    // Draw all objects to the window
    window.draw(paddles[0]);
    window.draw(paddles[1]);
    window.draw(ball);
}

void clean() {
    // Free up resources if necessary
}

int main() {
    // Create the game window
    sf::RenderWindow window(sf::VideoMode({gameWidth, gameHeight}), "PONG");
    window.setVerticalSyncEnabled(true);

    // Initialise game state
    init();

    sf::Clock clock;

    // Game loop
    while (window.isOpen()) {
        // Calculate delta time
        const float dt = clock.restart().asSeconds();

        // Handle input and window events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Clear, update logic, render, and present frame
        window.clear(sf::Color::Black);
        update(dt);
        render(window);
        window.display();
    }

    // Clean up and shutdown
    clean();
    return 0;
}