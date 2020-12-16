#pragma once

#include "Client.hpp"
#include "GUIElement.hpp"

#include <vector>
#include <memory>

class GUIElement;
class Client;
class Renderer
{
private:
    Client const* client;
    std::vector<std::shared_ptr<GUIElement> > elements;
public:
	Renderer(Client const&);

	void drawStatic();
	void addElement(std::shared_ptr<GUIElement>);
	void clearElements();
public:
    void setColor(Color const&);
    Color const& getColor();
    void drawRectangle(int,int,int,int);
    void drawCircle(int,int,int);
    void floodFill(int,int,int);
    void drawLine(int,int,int,int);
    void drawText(int,int,const char*);
    int getTextHeight(const char*);
    int getTextWidth(const char*);
};
