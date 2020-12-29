#include "Tile.hpp"

#include "Level.hpp"
#include "Logger.hpp"

Tile::Tile(Matrix const&initial,Vec2 const& pos,Color const& color,int type)
{
    this->pos = pos;
    state = 0;
    body[0] = initial;
    body[1] = body[0].turn();
    body[2] = body[1].turn();
    body[3] = body[2].turn();
    setColor(color);
    typeId = type;
}
Tile::Tile()
{
    state = 0;
}
Color const& Tile::getColor()const
{
    return color;
}
void Tile::setColor(Color const& color)
{
    this->color = color;
}
void Tile::turn(int times)
{
    state += times;
    state %= 4;
}
Matrix const& Tile::getBody()const
{
    return body[state % 4];
}
void Tile::setBody(Matrix const& bdy)
{
    body[0] = bdy;
    body[1] = body[0].turn();
    body[2] = body[1].turn();
    body[3] = body[2].turn();
}
Vec2 const& Tile::getPos()const
{
    return pos;
}
Vec2& Tile::getPos()
{
    return pos;
}
void Tile::setTypeId(int type)
{
    typeId = type;
}
int Tile::getTypeId()const
{
    return typeId;
}
