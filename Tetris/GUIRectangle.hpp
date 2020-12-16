#pragma once

#include "GUIElement.hpp"
#include "Color.hpp"
#include "Vec2.hpp"
#include "Renderer.hpp"

class Vec2;
class Renderer;
class GUIRectangle :public GUIElement
{
public:
    GUIRectangle(Vec2 const&,Vec2 const&,Color const&);

    virtual void draw(Renderer&);
};
