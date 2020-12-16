#pragma once

#include <memory>

#include "Vec2.hpp"

class Vec2;
class GUIElement;
class Renderer;
class Client;
class GUILabel;
class GUIRectangle;
class GUISheet;
class Level;
class GameScreen
{
private:
    Client* client;
    Renderer* renderer;
    std::shared_ptr<GUISheet> sheet;
    std::shared_ptr<GUIRectangle> backgroundLayer3;
    std::shared_ptr<GUIRectangle> backgroundLayer2;
    std::shared_ptr<GUIRectangle> backgroundLayer1;
    std::shared_ptr<GUISheet> sheetNext;
    std::shared_ptr<GUILabel> labelScore;
    std::shared_ptr<GUILabel> labelName;
    std::shared_ptr<GUILabel> labelGameOver;
    Vec2 gameUIPos;
    Vec2 gameUISize;
    int borderSize;
public:
    GameScreen(Client&,Renderer&,Vec2 const&,Vec2 const&,Vec2 const&,int,int,int);

    void render(Level const&);
};
