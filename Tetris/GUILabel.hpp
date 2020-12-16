#pragma once

#include "GUIElement.hpp"

#include <string>

class Renderer;
class GUILabel : public GUIElement
{
private:
    std::string label;
    bool singleLine;
    bool center;

    std::vector<std::string> splitContent;
public:
    GUILabel(Vec2 const& pos,Vec2 const& size,std::string const&content);
    GUILabel();

    virtual void setSingleLine(bool);
    virtual bool isSingleLine()const;
    virtual bool isCenter()const;
    virtual void setCenter(bool center);
    virtual void draw(Renderer&);
    virtual void setContent(std::string const&);
};
