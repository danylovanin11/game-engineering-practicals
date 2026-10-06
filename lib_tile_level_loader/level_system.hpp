#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <memory>
#include <string>
#include <vector>

// Static helper library: loads a tile level from a text file and renders it
class LevelSystem {
public:
    enum Tile { EMPTY, START, END, WALL, ENEMY, WAYPOINT };

    static void load_level(const std::string &path, float tile_size = 100.f);
    static void render(sf::RenderWindow &window);
    static sf::Color get_color(Tile t);
    static void set_color(Tile t, sf::Color c);
    // get tile at grid coordinate
    static Tile get_tile(sf::Vector2i p);
    // get screen-space coordinate of a tile (its top-left corner)
    static sf::Vector2f get_tile_position(sf::Vector2i p);
    // get the tile at a screen-space position
    static Tile get_tile_at(sf::Vector2f v);
    static int get_height();
    static int get_width();
    static float get_tile_size();
    static sf::Vector2f get_start_position();

protected:
    static std::unique_ptr<Tile[]> _tiles;    // internal array of tiles
    static int _width;                        // how many tiles wide the level is
    static int _height;                       // how many tiles high the level is
    static sf::Vector2f _offset;              // screen-space offset of the level
    static float _tile_size;                  // screen-space size of each tile
    static std::map<Tile, sf::Color> _colors; // colour to render each tile type
    static sf::Vector2f _start_position;      // top-left corner of the start tile

    // one rectangle per tile
    static std::vector<std::unique_ptr<sf::RectangleShape>> _sprites;
    // generates the _sprites array
    static void build_sprites();

private:
    LevelSystem() = delete;
    ~LevelSystem() = delete;
};