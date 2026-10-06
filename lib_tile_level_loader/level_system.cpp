#include "level_system.hpp"
#include <fstream>
#include <iostream>

// static members must be defined in exactly one .cpp
std::unique_ptr<LevelSystem::Tile[]> LevelSystem::_tiles;
int LevelSystem::_width = 0;
int LevelSystem::_height = 0;
sf::Vector2f LevelSystem::_offset(0.f, 0.f);
float LevelSystem::_tile_size(100.f);
sf::Vector2f LevelSystem::_start_position(0.f, 0.f);
std::vector<std::unique_ptr<sf::RectangleShape>> LevelSystem::_sprites;
std::map<LevelSystem::Tile, sf::Color> LevelSystem::_colors{
    {WALL, sf::Color::White}, {END, sf::Color::Red}};

int LevelSystem::get_height() { return _height; }
int LevelSystem::get_width() { return _width; }
float LevelSystem::get_tile_size() { return _tile_size; }
sf::Vector2f LevelSystem::get_start_position() { return _start_position; }

sf::Color LevelSystem::get_color(LevelSystem::Tile t) {
    // find() does not create the element, [] would
    auto it = _colors.find(t);
    if (it == _colors.end()) {
        _colors[t] = sf::Color::Transparent;
    }
    return _colors[t];
}

void LevelSystem::set_color(LevelSystem::Tile t, sf::Color c) {
    // creates the entry if it does not exist, replaces it otherwise
    _colors[t] = c;
}

void LevelSystem::load_level(const std::string &path, float tile_size) {
    _tile_size = tile_size;
    int w = 0, h = 0;
    std::string buffer;

    // load the whole file into buffer
    std::ifstream f(path);
    if (f.good()) {
        f.seekg(0, std::ios::end);
        buffer.resize(f.tellg());
        f.seekg(0);
        f.read(&buffer[0], buffer.size());
        f.close();
    } else {
        throw std::string("Couldn't open level file: ") + path;
    }

    int x = 0;
    std::vector<Tile> temp_tiles;
    for (size_t i = 0; i < buffer.size(); ++i) {
        const char c = buffer[i];
        switch (c) {
        case 'w':
            temp_tiles.push_back(WALL);
            break;
        case 's':
            temp_tiles.push_back(START);
            _start_position = get_tile_position({x, h});
            break;
        case 'e':
            temp_tiles.push_back(END);
            break;
        case ' ':
            temp_tiles.push_back(EMPTY);
            break;
        case '+':
            temp_tiles.push_back(WAYPOINT);
            break;
        case 'n':
            temp_tiles.push_back(ENEMY);
            break;
        case '\r':
            // Windows line ending: ignore
            continue;
        case '\n':
            // end of line: the first line gives the width
            if (w == 0) {
                w = x;
            }
            x = 0;
            h++;
            continue;
        default:
            std::cout << "Unknown tile type: " << c << std::endl;
            continue;
        }
        // only real tiles move the column forward
        x++;
    }

    if (temp_tiles.size() != static_cast<size_t>(w * h)) {
        throw std::string("Can't parse level file: ") + path;
    }
    _tiles = std::make_unique<Tile[]>(w * h);
    _width = w;
    _height = h;
    std::copy(temp_tiles.begin(), temp_tiles.end(), &_tiles[0]);
    std::cout << "Level " << path << " Loaded. " << w << "x" << h << std::endl;
    build_sprites();
}

void LevelSystem::build_sprites() {
    _sprites.clear();
    for (int y = 0; y < get_height(); ++y) {
        for (int x = 0; x < get_width(); ++x) {
            std::unique_ptr<sf::RectangleShape> s = std::make_unique<sf::RectangleShape>();
            s->setPosition(get_tile_position({x, y}));
            s->setSize(sf::Vector2f(_tile_size, _tile_size));
            s->setFillColor(get_color(get_tile({x, y})));
            _sprites.push_back(std::move(s));
        }
    }
}

sf::Vector2f LevelSystem::get_tile_position(sf::Vector2i p) {
    return sf::Vector2f(static_cast<float>(p.x), static_cast<float>(p.y)) * _tile_size + _offset;
}

LevelSystem::Tile LevelSystem::get_tile(sf::Vector2i p) {
    if (p.x < 0 || p.y < 0 || p.x >= _width || p.y >= _height) {
        throw std::string("Tile out of range: (") + std::to_string(p.x) + "," +
            std::to_string(p.y) + ")";
    }
    // 2D -> 1D: skip y full rows, then x tiles
    return _tiles[(p.y * _width) + p.x];
}

LevelSystem::Tile LevelSystem::get_tile_at(sf::Vector2f v) {
    const sf::Vector2f a = v - _offset;
    if (a.x < 0 || a.y < 0) {
        throw std::string("Tile out of range");
    }
    return get_tile(sf::Vector2i(a / _tile_size));
}

void LevelSystem::render(sf::RenderWindow &window) {
    for (const std::unique_ptr<sf::RectangleShape> &s : _sprites) {
        window.draw(*s);
    }
}