#ifndef COORD_H
#define COORD_H

#include "Tile.h"

class Coord {
public:

    Coord(int row, int col);
    Coord(int row, int col, Tile* tile);
    ~Coord();

    char getRow();
    int getCol();
    Tile* getTile();
    int getRowAsInt();

    void setPos(int row, int col);
    void setTile(Tile* tile);

    bool isCoordEmpty();

private:
    int row;
    int col;
    Tile* tile;
};


#endif