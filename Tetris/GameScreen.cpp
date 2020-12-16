#include "GameScreen.hpp"

#include <sstream>

#include "Vec2.hpp"
#include "GUISheet.hpp"
#include "GUIRectangle.hpp"
#include "GUICircle.hpp"
#include "GUILabel.hpp"
#include "Tile.hpp"
#include "Level.hpp"

GameScreen::GameScreen(Client& cl,Renderer& ren,Vec2 const&screenSize,Vec2 const& pos,Vec2 const& size,int borderSize,int pixels,int footHeight)
{
    client = &cl;
    renderer = &ren;
    gameUIPos = pos;
    gameUISize = size;


    int sheetNextPixels = (footHeight - borderSize) / 4;
    int sheetNextSize = sheetNextPixels * 4;
    int sheetNextPosY = gameUIPos.y + gameUISize.y + borderSize + (footHeight - borderSize - sheetNextSize) / 2;
    int sheetNextPosX = screenSize.x / 2 - sheetNextSize / 2;
    int labelHeight = 32;
    int labelPosY = gameUIPos.y + gameUISize.y + borderSize + footHeight / 2 - labelHeight / 2;
    int labelWidth = (gameUISize.x - borderSize * 4 - sheetNextSize) / 2;
    int labelPosX1 = gameUIPos.x + borderSize;
    int labelPosX2 = gameUIPos.x + borderSize * 3 + labelWidth + sheetNextSize;

    backgroundLayer1 = std::make_shared<GUIRectangle>(Vec2(0,0),Vec2(screenSize.x,screenSize.y),7);
    backgroundLayer2 = std::make_shared<GUIRectangle>(gameUIPos,gameUISize,0);
    backgroundLayer3 = std::make_shared<GUIRectangle>(Vec2(sheetNextPosX,sheetNextPosY),Vec2(sheetNextSize,sheetNextSize),0);
    sheet = std::make_shared<GUISheet>(gameUIPos,gameUISize,pixels);
    sheetNext = std::make_shared<GUISheet>(Vec2(sheetNextPosX,sheetNextPosY),Vec2(sheetNextSize,sheetNextSize),sheetNextPixels);
    labelName = std::make_shared<GUILabel>(Vec2(labelPosX1,labelPosY),Vec2(labelWidth,labelHeight),"Tetris by Listerily");
    labelScore = std::make_shared<GUILabel>(Vec2(labelPosX2,labelPosY),Vec2(labelWidth,labelHeight),"Score: 0");
    labelGameOver = std::make_shared<GUILabel>(Vec2(sheetNextPosX,labelPosY),Vec2(sheetNextSize,labelHeight),"Game Over");
}
void GameScreen::render(Level const& lv)
{
    renderer->clearElements();

    backgroundLayer1->setHollow(false);
    renderer->addElement(backgroundLayer1);

    backgroundLayer2->setHollow(false);
    renderer->addElement(backgroundLayer2);

    backgroundLayer3->setHollow(false);
    renderer->addElement(backgroundLayer3);

    sheet->clearBlocks();
    for(int i = 0;i < lv.col();++i)
    {
        for(int j = 0;j < lv.row();++j)
        {
            Vec2 pos(i,j);
            if(lv.getBlock(pos) != Level::BLOCK_VOID)
            {
                Color color = lv.getColor(pos);
                sheet->addBlock(pos,color,true);
            }
        }
    }
    renderer->addElement(sheet);

    std::stringstream stream;
    stream << "Score: " << client->getScore();
    labelScore->setCenter(true);
    labelScore->setSingleLine(true);
    labelScore->setContent(stream.str());
    labelScore->setColor(15);
    renderer->addElement(labelScore);

    labelName->setCenter(true);
    labelName->setSingleLine(true);
    labelName->setColor(15);
    renderer->addElement(labelName);

    sheetNext->clearBlocks();
    Tile const& nextTile = client->getNextTile();
    for(int i = 0;i < 4;++i)
    {
        for(int j = 0;j < 4;++j)
        {
            Vec2 pos(i,j);
            if(nextTile.getBody().at(i,j) == 1)
            {
                Color color = nextTile.getColor();
                sheetNext->addBlock(pos,color,true);
            }
            else
            {
                sheetNext->addBlock(pos,0,false);
            }
        }
    }

    labelGameOver->setCenter(true);
    labelGameOver->setSingleLine(true);
    labelGameOver->setColor(15);

    renderer->addElement(sheetNext);
    if(client->isGameOver())
        renderer->addElement(labelGameOver);


    renderer->drawStatic();
}
