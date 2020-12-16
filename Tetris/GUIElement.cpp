#include "GUIElement.hpp"

#include "Vec2.hpp"

GUIElement::GUIElement()
{
    visible = true;
}
void GUIElement::draw(Renderer& renderer)
{
    int size = children.size();
    for(int i = 0;i < size;++i)
    {
        children[i]->draw(renderer);
    }
}
void GUIElement::setColor(Color const& color)
{
    this->color = color;
}
void GUIElement::setHollow(bool hollow)
{
    this->hollow = hollow;
}
void GUIElement::setPos(Vec2 const&pos)
{
    this->pos = pos;
}
void GUIElement::setSize(Vec2 const&size)
{
    this->size = size;
}
Color const& GUIElement::getColor()const
{
    return color;
}
bool GUIElement::isHollow()
{
    return hollow;
}
bool GUIElement::isVisible()const
{
    return visible;
}
void GUIElement::setVisible(bool visible)
{
    this->visible = visible;
}
Vec2 const& GUIElement::getPos()const
{
    return pos;
}
Vec2 const& GUIElement::getSize()const
{
    return size;
}
void GUIElement::addChild(std::shared_ptr<GUIElement> child)
{
    children.push_back(child);
}
void GUIElement::clearChildren()
{
    children.clear();
}
std::vector<std::shared_ptr<GUIElement> >& GUIElement::getChildren()
{
    return children;
}
std::vector<std::shared_ptr<GUIElement> > const& GUIElement::getChildren()const
{
    return children;
}
