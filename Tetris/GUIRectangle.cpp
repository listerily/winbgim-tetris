#include "GUIRectangle.hpp"

GUIRectangle::GUIRectangle(Vec2 const&p,Vec2 const& s,Color const& c)
{
    pos = p;
    size = s;
    color = c;
}
void GUIRectangle::draw(Renderer& renderer)
{
    renderer.setColor(color);
    renderer.drawRectangle(pos.x,pos.y,pos.x + size.x,pos.y + size.y);
    if(!hollow)
    {
        renderer.floodFill((pos.x + pos.x + size.x) / 2,(pos.y + pos.y + size.y) / 2,color);
    }
}
