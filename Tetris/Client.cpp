#include "Client.hpp"

#include <graphics.h>
#include <cmath>
#include <vector>
#include <memory>
#include <iostream>
#include <cstdio>

#include "Vec2.hpp"
#include "Tile.hpp"
#include "Level.hpp"
#include "Renderer.hpp"
#include "GameScreen.hpp"

Client::Client()
{
    pixels = 32;
    rows = 17;
    cols = 12;
    footHeight = 100;
    gameWidth = pixels * cols;
    gameHeight = pixels * rows;
    windowWidth = gameWidth + 20;
    windowHeight =gameHeight + 20 + footHeight;
    gamePoint = Vec2(10,10);
    initwindow(windowWidth,windowHeight,"Tetris");
    renderer = new Renderer(*this);
    screen = new GameScreen(*this,*renderer,Vec2(windowWidth,windowHeight),gamePoint,Vec2(gameWidth,gameHeight),10,pixels,footHeight);

    printTutorials();
    Level::initializeEntities();
}
Client::~Client()
{
    closegraph();
    delete renderer;
    delete screen;
    if(level != NULL)
        delete level;
}
void Client::printTutorials()const
{
    printf("===============INFO==============\n");
    printf("| Tetris - Winbgim ,Version 1.0 |\n");
    printf("| By Listerily                  |\n");
    printf("=============TUTORIALS===========\n");
    printf("| Press Keys to control game.   |\n");
    printf("| 'Q': Turn the blocks (Left).  |\n");
    printf("| 'E': Turn the blocks (Right). |\n");
    printf("| 'S': Downwards.               |\n");
    printf("| 'A': Leftwards.               |\n");
    printf("| 'D': Rightwards.              |\n");
    printf("| 'C': Clear all blocks.        |\n");
    printf("| 'R': Reset current blocks.    |\n");
    printf("| 'T': Restart the game.        |\n");
    printf("=================================\n");
}
void Client::start()
{
    level = new Level(17,12);
    level->start();
    guiTick();
    unsigned long long timer = 1;
    while(true)
    {
        gameTick();
        guiTick();
        ++timer;
    }
    pause();
}
int Client::getScore()const
{
    if(!level->started())
        return 0;
    return level->getScore();
}
Tile const& Client::getNextTile()const
{
    return level->getNextTile();
}
bool Client::isGameOver()const
{
    return level->isGameOver();
}
int Client::getWindowHeight()const
{
    return windowHeight;
}
int Client::getWindowWidth()const
{
    return windowWidth;
}
void Client::pause()
{
    getch();
}
void Client::gameTick()
{
    static bool initial = true;
    if(initial)
    {
        level->tick(Level::EVENT_NONE);
        initial = false;
        return;
    }

    int event = Level::EVENT_NONE;
    int key = getch();
    switch(key)
    {
    case 's':
    case 'S':
        event = Level::EVENT_DOWN;
        break;
    case 'q':
    case 'Q':
        event = Level::EVENT_TURN_LEFT;
        break;
    case 'w':
    case 'W':
        event = Level::EVENT_NONE;
        break;
    case 'a':
    case 'A':
        event = Level::EVENT_LEFT;
        break;
    case 'd':
    case 'D':
        event = Level::EVENT_RIGHT;
        break;
    case 'e':
    case 'E':
        event = Level::EVENT_TURN_RIGHT;
        break;
    case 'r':
    case 'R':
        event = Level::EVENT_REGEN;
        break;
    case 'c':
    case 'C':
        event = Level::EVENT_CLEAR;
        break;
    case 't':
    case 'T':
        event = Level::EVENT_RESTART;
        break;
    }

    level->tick(event);
}

void Client::guiTick()
{
    screen->render(*level);
}
