
#ifndef SQUARE_H
#define SQUARE_H

#include <iostream>
#include "Coord.h"

class Square{
public:

   //Constructor
    Square(Coord* coord);
    Square();
    ~Square();

    std::string getValue();
    Coord* getCoord();

    void setValue(std::string v);
    void setValue(Tile* tile);
    void setCoord(Coord* c);

    void printSquare();

private: 
   std::string value;
   Coord* coord = new Coord('!', -1);

};

#endif 