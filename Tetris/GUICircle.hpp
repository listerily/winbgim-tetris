#pragma once

#include "GUIElement.hpp"
#include "Color.hpp"

class Vec2;
class Renderer;
class GUICircle : public GUIElement
{
private:
    int radius;
public:
    GUICircle(Vec2 const&pos,int radius,Color const& color);
    int getRadius()const;

    virtual void draw(Renderer&)const;
};
