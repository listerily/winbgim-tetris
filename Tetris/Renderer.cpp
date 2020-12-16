#include "Renderer.hpp"

#include "GUIElement.hpp"

#include <graphics.h>

Renderer::Renderer(Client const& client)
{
    this->client = &client;
}

void Renderer::drawStatic()
{
    int size = elements.size();
    for(int i = 0;i < size;++i)
    {
        if(elements[i]->isVisible())
            elements[i]->draw(*this);
    }
}
void Renderer::addElement(std::shared_ptr<GUIElement> element)
{
    elements.push_back(element);
}
void Renderer::clearElements()
{
    elements.clear();
}
void Renderer::setColor(Color const& color)
{
    setcolor(color);
}
Color const& Renderer::getColor()
{
    static Color color;
    color = getcolor();
    return color;
}
void Renderer::drawRectangle(int x1,int y1,int x2,int y2)
{
    rectangle(x1,y1,x2,y2);
}
void Renderer::drawCircle(int x,int y,int r)
{
    circle(x,y,r);
}
void Renderer::floodFill(int x,int y,int border)
{
    setfillstyle(SOLID_FILL, border);
    floodfill(x,y,border);
}
void Renderer::drawLine(int x1,int y1,int x2,int y2)
{
    line(x1,y1,x2,y2);
}
void Renderer::drawText(int x,int y,const char* str)
{
    outtextxy(x,y,str);
}
int Renderer::getTextHeight(const char* str)
{
    return textheight(str);
}
int Renderer::getTextWidth(const char* str)
{
    return textwidth(str);
}
