#include "GUIElement.hpp"

#include <vector>
#include <memory>

#include "Color.hpp"

class GUIRectangle;
class GUISheet : public GUIElement
{
private:
    int pixels;
    int cols;
    int rows;
public:
    GUISheet(Vec2 const&,Vec2 const&,int);

    int getColCount()const;
    int getRowCount()const;
    std::shared_ptr<GUIRectangle> addBlock(Vec2 const&,Color const&,bool);
    void clearBlocks();

    virtual void draw(Renderer&);
};
