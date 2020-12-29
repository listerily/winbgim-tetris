#include "Client.hpp"

#include <graphics.h>
#include <cmath>
#include <vector>
#include <memory>
#include <iostream>
#include <cstdio>
#include <ctime>
#include <cstdlib>

#include "Vec2.hpp"
#include "Tile.hpp"
#include "Level.hpp"
#include "Renderer.hpp"
#include "GameScreen.hpp"
#include "KeyEventListener.hpp"

Client::Client()
{
    srand(time(0));
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
    listener = new KeyEventListener();
    printTutorials();
    Level::initializeEntities();
}
Client::~Client()
{
    closegraph();
    delete renderer;
    delete screen;
    delete listener;
    if(level != NULL)
        delete level;
}
void Client::printTutorials()const
{
    printf("===============INFO==============\n");
    printf("| Tetris - Winbgim ,Version 1.1 |\n");
    printf("| By Listerily                  |\n");
    printf("=============TUTORIALS===========\n");
    printf("| Press Keys to control game.   |\n");
    printf("| 'Q': Turn the blocks (Left).  |\n");
    printf("| 'E': Turn the blocks (Right). |\n");
    printf("| 'A': Leftwards.               |\n");
    printf("| 'D': Rightwards.              |\n");
    printf("| 'S': Downwards.               |\n");
    printf("| 'M': Mirror the blocks.       |\n");
    printf("| 'B': Return blocks back.      |\n");
    printf("| 'C': Clear all blocks.        |\n");
    printf("| 'R': Reset current blocks.    |\n");
    printf("| 'T': Restart the game.        |\n");
    printf("=================================\n");
}
void Client::start()
{
    level = new Level(17,12);
    level->start();
    clock_t start = clock();
    clock_t lastTimer = start / 300;
    while(true)
    {
        clock_t timer = clock() - start;
        if(timer / 300 > lastTimer)
        {
            normalEvent();
            flushGraphics();
        }
        else if(!listener->isEmpty())
        {
            int key = listener->readKey();
            handleKeyEvent(key);
            flushGraphics();
        }
        lastTimer = timer / 300;
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
void Client::flushGraphics()
{
    screen->render(*level);
}
void Client::normalEvent()
{
    level->tick(Level::EVENT_DOWN);
}
void Client::handleKeyEvent(int key)
{
    int event = Level::EVENT_NONE;
    switch(key)
    {
    case 'q':
    case 'Q':
        event = Level::EVENT_TURN_LEFT;
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
    case 'm':
    case 'M':
        event = Level::EVENT_MIRROR;
        break;
    case 'b':
    case 'B':
        event = Level::EVENT_BACK;
        break;
    case 's':
    case 'S':
        event = Level::EVENT_DOWN;
        break;
    }

    level->tick(event);
}
