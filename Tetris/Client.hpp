#pragma once

#include "Vec2.hpp"

class Renderer;
class Level;
class GameScreen;
class Tile;
class Client
{
private:
    int windowWidth;
    int windowHeight;
    Vec2 gamePoint;
    int gameWidth;
    int gameHeight;
    int pixels;
    int rows;
    int cols;
    int footHeight;
	Renderer* renderer;
    Level* level;
    GameScreen* screen;
private:
    void guiTick();
    void gameTick();
public:
    Client();
    ~Client();
public:
    void start();
    int getWindowWidth()const;
    int getWindowHeight()const;
    void pause();
    int getScore()const;
    bool isGameOver()const;
    Tile const& getNextTile()const;
    void printTutorials()const;
};
