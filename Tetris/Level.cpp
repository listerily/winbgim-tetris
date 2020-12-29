#include "Level.hpp"

#include "Tile.hpp"
#include "Vec2.hpp"
#include "Renderer.hpp"

#include <vector>
#include <cstdlib>
#include <cassert>

Matrix Level::TILE_ENTITY[7];
Level::Level(int rows,int cols)
{
    this->rows = rows;
    this->cols = cols;
    _started = false;
    _gameOver = false;
    _score = 0;
    hasFallingTile = false;
    fallenBlocks = Matrix(rows,cols);
    colorBlocks = Matrix(rows,cols);
    summonNextTile();
}
Level::~Level()
{

}
void Level::tick(int event)
{
    if(!started())
        return;

    if(event == EVENT_RESTART)
    {
        _gameOver = false;
        _score = 0;
        colorBlocks = Matrix(rows,cols);
        fallenBlocks = Matrix(rows,cols);
        summonNextTile();
        summonFallingTile();
        hasFallingTile = true;
        return;
    }

    if(isGameOver())
        return;

    if(event == EVENT_CLEAR)
    {
        colorBlocks = Matrix(rows,cols);
        fallenBlocks = Matrix(rows,cols);
    }

    if(event == EVENT_BACK)
    {
        fallingTile = fallingTileBack;
    }

    if(!hasFallingTile || event == EVENT_REGEN)
    {
        if(!summonFallingTile())
        {
            _gameOver = true;
            return;
        }
        hasFallingTile = true;
        return;
    }

    if(event == EVENT_TURN_LEFT || event == EVENT_TURN_RIGHT || EVENT_MIRROR)
    {
        Tile turnedTile = fallingTile;

        if(event == EVENT_TURN_LEFT)
            turnedTile.turn(3);
        else if(event == EVENT_TURN_RIGHT)
            turnedTile.turn(1);
        else if(event == EVENT_MIRROR)
        {
            int typeAfterMirror = getMirrorTypeOfFalingTile();
            if(typeAfterMirror != -1)
            {
                turnedTile.setBody(TILE_ENTITY[typeAfterMirror]);
                turnedTile.setTypeId(typeAfterMirror);
            }
        }

        int max_times;
        bool shouldAdjust;
        Tile turnedTile_Adjusted;

        max_times = 2;
        shouldAdjust = false;
        turnedTile_Adjusted = turnedTile;
        while(!fitable(turnedTile_Adjusted) && --max_times)
        {
            shouldAdjust = true;
            turnedTile_Adjusted.getPos().x++;
        }
        if(shouldAdjust && fitable(turnedTile_Adjusted))
            turnedTile = turnedTile_Adjusted;

        max_times = 2;
        shouldAdjust = false;
        turnedTile_Adjusted = turnedTile;
        while(!fitable(turnedTile_Adjusted) && --max_times)
        {
            shouldAdjust = true;
            turnedTile_Adjusted.getPos().x--;
        }
        if(shouldAdjust && fitable(turnedTile_Adjusted))
            turnedTile = turnedTile_Adjusted;

        max_times = 2;
        shouldAdjust = false;
        turnedTile_Adjusted = turnedTile;
        while(!fitable(turnedTile_Adjusted) && --max_times)
        {
            shouldAdjust = true;
            turnedTile_Adjusted.getPos().y--;
        }
        if(shouldAdjust && fitable(turnedTile_Adjusted))
            turnedTile = turnedTile_Adjusted;

        max_times = 3;
        shouldAdjust = false;
        turnedTile_Adjusted = turnedTile;
        while(!fitable(turnedTile_Adjusted) && --max_times)
        {
            shouldAdjust = true;
            turnedTile_Adjusted.getPos().y++;
        }
        if(shouldAdjust && fitable(turnedTile_Adjusted))
            turnedTile = turnedTile_Adjusted;

        if(fitable(turnedTile))
            fallingTile = turnedTile;
    }

    if(event == EVENT_LEFT)
    {
        fallingTile.getPos().x--;
        if(!fitable(fallingTile))
           fallingTile.getPos().x++;
    }

    if(event == EVENT_RIGHT)
    {
        fallingTile.getPos().x++;
        if(!fitable(fallingTile))
           fallingTile.getPos().x--;
    }

    if(event == EVENT_DOWN)
    {
        fallingTile.getPos().y++;
        if(fitable(fallingTile))
            return;
        hasFallingTile = false;
        fallingTile.getPos().y--;
        for(int x = 0;x < 4;++x)
            for(int y = 0;y < 4;++y)
                if(fallingTile.getBody().at(x,y) == 1)
                    fallenBlocks.at(fallingTile.getPos().x + x,fallingTile.getPos().y + y) = 1;
        for(int x = 0;x < 4;++x)
            for(int y = 0;y < 4;++y)
                if(fallingTile.getBody().at(x,y) == 1)
                    colorBlocks.at(fallingTile.getPos().x + x,fallingTile.getPos().y + y) = fallingTile.getColor();

        while(true)
        {
            for(int i = 0;i < rows;++i)
            {
                bool solid = true;
                for(int j = 0;j < cols;++j)
                {
                    if(fallenBlocks.at(j,i) == 0)
                    {
                        solid = false;
                    }
                }

                if(solid)
                {
                    ++_score;
                    for(int j = 0;j < cols;++j)
                    {
                        fallenBlocks.at(j,i) = 0;
                        colorBlocks.at(j,i) = 0;
                    }
                    for(int _i = i;_i > 0;--_i)
                    {
                        for(int _j = 0;_j < cols;++_j)
                        {
                            fallenBlocks.at(_j,_i) = fallenBlocks.at(_j,_i - 1);
                            colorBlocks.at(_j,_i) = colorBlocks.at(_j,_i - 1);
                        }
                    }
                    goto NEXT_WHILE_LOOP;
                }
            }
            goto END_DETECTING;
            NEXT_WHILE_LOOP:;
        }
        END_DETECTING:;
    }

}
int Level::getMirrorTypeOfFalingTile()const
{
    int typeIdAfterMirror = -1;
    switch(fallingTile.getTypeId())
    {
    case 0:
        typeIdAfterMirror = 6;
        break;
    case 6:
        typeIdAfterMirror = 0;
        break;
    case 3:
        typeIdAfterMirror = 4;
        break;
    case 4:
        typeIdAfterMirror = 3;
        break;
    }
    return typeIdAfterMirror;
}
Tile const& Level::getNextTile()const
{
    return nextTile;
}
void Level::summonNextTile()
{
    int type = rand() % 7;
    Vec2 initial_pos = Vec2(0,0);
    Color color = (rand() % 14) + 1;
    nextTile = Tile(TILE_ENTITY[type],initial_pos,color,type);
    nextTile.turn(rand() % 4);
}
bool Level::summonFallingTile()
{
    Tile newTile = nextTile;
    summonNextTile();

    do{
        newTile.getPos().y--;
    }while(fitableIgnoreTiles(newTile));
    newTile.getPos().y++;
    int borderLeft;
    int borderRight;
    do{
        newTile.getPos().x--;
    }while(fitableIgnoreTiles(newTile));
    borderLeft = ++newTile.getPos().x;
    do{
        newTile.getPos().x++;
    }while(fitableIgnoreTiles(newTile));
    borderRight = --newTile.getPos().x;
    int offset = rand() % (borderRight - borderLeft + 1);

    for(int i = borderLeft;i <= borderRight;++i)
    {
        newTile.getPos().x = i;
        if(!fitable(newTile))
            return false;
    }
    newTile.getPos().x = borderLeft + offset;

    fallingTile = newTile;
    fallingTileBack = newTile;
    return true;
}
bool Level::fitableIgnoreTiles(Tile const& tile)const
{
    for(int selfx = 0;selfx < 4;++selfx)
        for(int selfy = 0;selfy < 4;++selfy)
            if(tile.getBody().at(selfx,selfy) == 1)
            {
                Vec2 detectPos = tile.getPos().offset(selfx,selfy);
                if(detectPos.x < 0 || detectPos.x >= col() || detectPos.y < 0 || detectPos.y >= row())
                    return false;
            }
    return true;
}
bool Level::fitable(Tile const& tile)const
{
    for(int selfx = 0;selfx < 4;++selfx)
        for(int selfy = 0;selfy < 4;++selfy)
            if(tile.getBody().at(selfx,selfy) == 1
                && selfx + tile.getPos().x >= 0
                && selfx + tile.getPos().x < cols
                && selfy + tile.getPos().y >= 0
                && selfy + tile.getPos().y < rows
                && fallenBlocks.at(selfx + tile.getPos().x,selfy + tile.getPos().y) == 1)
                return false;

    for(int selfx = 0;selfx < 4;++selfx)
        for(int selfy = 0;selfy < 4;++selfy)
            if(tile.getBody().at(selfx,selfy) == 1)
            {
                Vec2 detectPos = tile.getPos().offset(selfx,selfy);
                if(detectPos.x < 0 || detectPos.x >= col() || detectPos.y < 0 || detectPos.y >= row())
                    return false;
            }
    return true;
}
void Level::start()
{
    _started = true;
}
int Level::col()const
{
    return cols;
}
int Level::row()const
{
    return rows;
}
int Level::getBlock(Vec2 const& pos)const
{
    if(!started())
        return BLOCK_VOID;
    if(fallenBlocks.at(pos.x,pos.y) == 1)
        return BLOCK_TILE;
    if(hasFallingTile)
        for(int x = 0;x < 4;++x)
            for(int y = 0;y < 4;++y)
                if(fallingTile.getBody().at(x,y) == 1
                   && x == pos.x - fallingTile.getPos().x
                   && y == pos.y - fallingTile.getPos().y)
                    return BLOCK_TILE;
    return BLOCK_VOID;
}
Color const& Level::getColor(Vec2 const& pos)const
{
    static Color const defaultColor = 0;
    if(!started())
        return defaultColor;
    if(hasFallingTile)
        for(int x = 0;x < 4;++x)
            for(int y = 0;y < 4;++y)
                if(fallingTile.getBody().at(x,y) == 1
                   && x == pos.x - fallingTile.getPos().x
                   && y == pos.y - fallingTile.getPos().y)
                    return fallingTile.getColor();
    return colorBlocks.at(pos.x,pos.y);
}
bool Level::isGameOver()const
{
    return _gameOver;
}
bool Level::started()const
{
    return _started;
}
int Level::getScore()const
{
    if(!started())
        return 0;
    return _score;
}

void Level::initializeEntities()
{
    int entity_item_1[4][4] =
    {
        {0,1,1,0},
        {0,0,1,0},
        {0,0,1,0},
        {0,0,0,0}
    };
    TILE_ENTITY[0] = Matrix(4,4);
    for(int i = 0;i < 4;++i)
        for(int j = 0;j < 4;++j)
            TILE_ENTITY[0].at(i,j) = entity_item_1[i][j];
    int entity_item_2[4][4] =
    {
        {0,0,0,0},
        {0,1,1,1},
        {0,0,1,0},
        {0,0,0,0}
    };
    TILE_ENTITY[1] = Matrix(4,4);
    for(int i = 0;i < 4;++i)
        for(int j = 0;j < 4;++j)
            TILE_ENTITY[1].at(i,j) = entity_item_2[i][j];
    int entity_item_3[4][4] =
    {
        {0,1,0,0},
        {0,1,0,0},
        {0,1,0,0},
        {0,1,0,0}
    };
    TILE_ENTITY[2] = Matrix(4,4);
    for(int i = 0;i < 4;++i)
        for(int j = 0;j < 4;++j)
            TILE_ENTITY[2].at(i,j) = entity_item_3[i][j];
    int entity_item_4[4][4] =
    {
        {0,1,0,0},
        {0,1,1,0},
        {0,0,1,0},
        {0,0,0,0}
    };
    TILE_ENTITY[3] = Matrix(4,4);
    for(int i = 0;i < 4;++i)
        for(int j = 0;j < 4;++j)
            TILE_ENTITY[3].at(i,j) = entity_item_4[i][j];
    int entity_item_5[4][4] =
    {
        {0,0,1,0},
        {0,1,1,0},
        {0,1,0,0},
        {0,0,0,0}
    };
    TILE_ENTITY[4] = Matrix(4,4);
    for(int i = 0;i < 4;++i)
        for(int j = 0;j < 4;++j)
            TILE_ENTITY[4].at(i,j) = entity_item_5[i][j];
    int entity_item_6[4][4] =
    {
        {0,0,0,0},
        {0,1,1,0},
        {0,1,1,0},
        {0,0,0,0}
    };
    TILE_ENTITY[5] = Matrix(4,4);
    for(int i = 0;i < 4;++i)
        for(int j = 0;j < 4;++j)
            TILE_ENTITY[5].at(i,j) = entity_item_6[i][j];
    int entity_item_7[4][4] =
    {
        {0,1,1,0},
        {0,1,0,0},
        {0,1,0,0},
        {0,0,0,0}
    };
    TILE_ENTITY[6] = Matrix(4,4);
    for(int i = 0;i < 4;++i)
        for(int j = 0;j < 4;++j)
            TILE_ENTITY[6].at(i,j) = entity_item_7[i][j];
}
