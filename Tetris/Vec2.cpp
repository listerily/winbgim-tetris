#include "Vec2.hpp"


Vec2::Vec2(int x,int y)
{
    this->x = x;
    this->y = y;
}
Vec2::Vec2()
{
    x = 0;
    y = 0;
}
Vec2::Vec2(Vec2 const& v)
{
    x = v.x;
    y = v.y;
}
int Vec2::getX()const
{
    return x;
}
int Vec2::getY()const
{
    return y;
}
bool Vec2::operator<(Vec2 const&v)const
{
    if(x == v.x)
        return y < v.y;
    return x < v.x;
}
bool Vec2::operator>(Vec2 const&v)const
{
    if(x == v.x)
        return y > v.y;
    return x > v.x;
}
bool Vec2::operator<=(Vec2 const&v)const
{
    if(x == v.x)
        return y <= v.y;
    return x <= v.x;
}
bool Vec2::operator>=(Vec2 const&v)const
{
    if(x == v.x)
        return y >= v.y;
    return x >= v.x;
}
bool Vec2::operator==(Vec2 const&v)const
{
    return x == v.x && y == v.y;
}
bool Vec2::operator!=(Vec2 const&v)const
{
    return x != v.x || y != v.y;
}
Vec2 Vec2::offset(Vec2 const& v)const
{
    return Vec2(x + v.x,y + v.y);
}
Vec2 Vec2::offset(int xx,int yy)const
{
    return Vec2(x + xx,y + yy);
}
