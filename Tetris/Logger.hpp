#pragma once

#include <list>

class Vec2;
class Logger
{
public:
    static void printSnakeBody(std::list<Vec2> const&);
};
