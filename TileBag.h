#ifndef TILEBAG_H
#define TILEBAG_H

#include "LinkedList.h"

//#include <iostream>

class TileBag {
public:
    // Constructor
    TileBag();

    // Deconstructor
    ~TileBag();

    void generateTiles();
    Tile* drawTile();
    int getTileBagSize();
    void addTile(Tile*);
    //for testing 
    void printTileBag();
    std::string getTileBag();
    void setSeed(unsigned);

private:
    LinkedList* tileBag;
    unsigned seed = 1;

};

#endif 