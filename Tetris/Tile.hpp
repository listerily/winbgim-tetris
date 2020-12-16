#pragma once

#include <list>
#include <vector>
#include <map>

#include "Vec2.hpp"
#include "Matrix.hpp"
#include "Color.hpp"

class Level;
class Vec2;
class Tile
{
private:
    Matrix body[4];
    Vec2 pos;
    int color;
    int state;
public:
    Tile(Matrix const& initial,Vec2 const& pos,Color const&color);
    Tile();
public:
    Color const& getColor()const;
    void setColor(Color const& color);
    void turn(int times);
    Matrix const& getBody()const;
    Vec2 const& getPos()const;
    Vec2& getPos();
};
