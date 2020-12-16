#include "Logger.hpp"

#include "Vec2.hpp"

#include <iostream>
#include <sstream>
#include <cstdio>

void Logger::printSnakeBody(std::list<Vec2> const& body)
{
    for(auto iter = body.begin();iter != body.end();++iter)
    {
        Vec2 const& section = *iter;
        std::cout << "(" << section.x << "," << section.y << ")";
    }
    std::cout << std::endl;
}
