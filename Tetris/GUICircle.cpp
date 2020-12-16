#include "GUICircle.hpp"

#include <graphics.h>

GUICircle::GUICircle(Vec2 const&pos,int radius,Color const& color)
{
    this->pos = pos;
    this->size = Vec2(radius,radius);
    this->radius = radius;
    this->color = color;
}
int GUICircle::getRadius()const
{
    return radius;
}
void GUICircle::draw(Renderer& renderer)const
{
    setcolor(color);
    circle(pos.x,pos.y,radius);
    if(!hollow)
    {
        setfillstyle(SOLID_FILL, color);
        floodfill(pos.x,pos.y,color);
    }
}
