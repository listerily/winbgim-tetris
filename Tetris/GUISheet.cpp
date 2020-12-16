#include "GUISheet.hpp"

#include "GUIRectangle.hpp"

GUISheet::GUISheet(Vec2 const& position,Vec2 const& size,int pixels)
{
    this->pos = position;
    this->size = size;

    this->pixels = pixels;

    cols = (size.x) / pixels;
    rows = (size.y) / pixels;
}
int GUISheet::getColCount()const
{
    return cols;
}
int GUISheet::getRowCount()const
{
    return rows;
}
std::shared_ptr<GUIRectangle> GUISheet::addBlock(Vec2 const&position,Color const& color,bool hasBorder)
{
    Vec2 rectanglePos = Vec2(pos.x + position.x * pixels,pos.y + position.y * pixels);
    Vec2 rectangleSize = Vec2(pixels,pixels);

    std::shared_ptr<GUIRectangle> newBlock = std::make_shared<GUIRectangle>(rectanglePos,rectangleSize,color);
    newBlock->setHollow(false);
    addChild(newBlock);

    if(hasBorder)
    {
        std::shared_ptr<GUIRectangle> newBlock2 = std::make_shared<GUIRectangle>(rectanglePos,rectangleSize,15);
        newBlock2->setHollow(true);
        addChild(newBlock2);
    }

    return newBlock;
}
void GUISheet::draw(Renderer& renderer)
{
    GUIElement::draw(renderer);
}
void GUISheet::clearBlocks()
{
    clearChildren();
}
