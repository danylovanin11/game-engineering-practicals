#pragma once
#include <memory>
#include <string>
#include "game_system.hpp"

class MazeScene : public Scene {
public:
    MazeScene() = default;
    void update(const float &dt) override;
    void render(sf::RenderWindow &window) override;
    void load() override;
    void reset();
    void set_file_path(const std::string &file_path);

private:
    std::string _file_path;
};

class EndScene : public Scene {
public:
    EndScene() = default;
    void load() override;
    void render(sf::RenderWindow &window) override;

private:
    sf::Text win_text;
    sf::Font font;
};

// every scene of the game, reachable from anywhere in the code
struct Scenes {
    static std::shared_ptr<Scene> maze;
    static std::shared_ptr<Scene> end;
};