#pragma once

#include "Vec2.hpp"
#include "Color.hpp"
#include "Matrix.hpp"
#include "Tile.hpp"

#include <vector>
#include <memory>

class Vec2;
class Level
{
private:
    int cols;
    int rows;
    bool _started;
    bool _gameOver;
    int _score;
    Tile fallingTile;
    Tile nextTile;
    Tile fallingTileBack;
    bool hasFallingTile;
    Matrix fallenBlocks;
    Matrix colorBlocks;
public:
    Level(int rows,int cols);
    ~Level();
    void tick(int);
    void start();
    int col()const;
    int row()const;
    int getBlock(Vec2 const&)const;
    Color const& getColor(Vec2 const&)const;
    bool isGameOver()const;
    bool started()const;
    int getScore()const;
    bool summonFallingTile();
    void summonNextTile();
    bool fitableIgnoreTiles(Tile const&)const;
    bool fitable(Tile const&)const;
    Tile const& getNextTile()const;
    int getMirrorTypeOfFalingTile()const;
public:
    static const int BLOCK_VOID = 0;
    static const int BLOCK_TILE = 1;
public:
    static const int EVENT_NONE = 0x0;
    static const int EVENT_DOWN = 0x1;
    static const int EVENT_LEFT = 0x2;
    static const int EVENT_RIGHT = 0x3;
    static const int EVENT_TURN_LEFT = 0x4;
    static const int EVENT_TURN_RIGHT = 0x5;
    static const int EVENT_REGEN = 0x6;
    static const int EVENT_CLEAR = 0x7;
    static const int EVENT_RESTART = 0x8;
    static const int EVENT_MIRROR = 0x9;
    static const int EVENT_BACK = 0xa;
public:
    static Matrix TILE_ENTITY[7];
    static void initializeEntities();
};
