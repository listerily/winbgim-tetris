#pragma once

class Vec2
{
public:
    int x;
    int y;
public:
    Vec2(int,int);
    Vec2();
    Vec2(Vec2 const&);

    int getX()const;
    int getY()const;

    bool operator<(Vec2 const&)const;
    bool operator>(Vec2 const&)const;
    bool operator<=(Vec2 const&)const;
    bool operator>=(Vec2 const&)const;
    bool operator==(Vec2 const&)const;
    bool operator!=(Vec2 const&)const;

    Vec2 offset(Vec2 const&)const;
    Vec2 offset(int,int)const;
};
