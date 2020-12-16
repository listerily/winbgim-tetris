#pragma once

#include "Vec2.hpp"
#include "Color.hpp"

#include <vector>
#include <memory>

class Vec2;
class Renderer;
class GUIElement
{
protected:
    Vec2 pos,size;
    Color color;
    bool hollow;
    bool visible;
    std::vector<std::shared_ptr<GUIElement> > children;
public:
    GUIElement();
public:
    virtual void draw(Renderer&);
    virtual void setColor(Color const&);
    virtual void setHollow(bool);
    virtual void setPos(Vec2 const&);
    virtual void setSize(Vec2 const&);
    virtual Color const& getColor()const;
    virtual bool isHollow();
    virtual bool isVisible()const;
    virtual void setVisible(bool visible);
    virtual Vec2 const& getPos()const;
    virtual Vec2 const& getSize()const;
    virtual void addChild(std::shared_ptr<GUIElement>);
    virtual void clearChildren();
    virtual std::vector<std::shared_ptr<GUIElement> >& getChildren();
    virtual std::vector<std::shared_ptr<GUIElement> > const& getChildren()const;
};
