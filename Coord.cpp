#include "Coord.h"
#include <iostream>

Coord::Coord(int row, int col) {
    this->row = row;
    this->col = col;
    this->tile = nullptr;
}

Coord::Coord(int row, int col, Tile* tile) {
    this->row = row;
    this->col = col;
    this->tile = tile;
}

Coord::~Coord() {
    if (tile != nullptr) {
        delete tile;
        tile = nullptr;
    }
}

// Getters
char Coord::getRow() {
    return char(row + 64);
}

int Coord::getCol() {
    return col;
}

Tile* Coord::getTile() {
    return tile;
}

int Coord::getRowAsInt(){
    return row;
}

// Setters
void Coord::setTile(Tile* tile) {
    this->tile = tile;
}

void Coord::setPos(int row, int col) {
    this->row = row;
    this->col = col;
}


bool Coord::isCoordEmpty(){
    bool isEmpty = true;

    if(tile != nullptr){
        isEmpty = false;
    }

    return isEmpty;
}