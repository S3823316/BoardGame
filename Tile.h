
#ifndef ASSIGN2_TILE_H
#define ASSIGN2_TILE_H

#include "TileCodes.h"
#include <string>

// Define a Colour type
typedef char Colour;

// Define a Shape type
typedef int Shape;

class Tile {
public:

   //Constructor
   Tile(Colour c, Shape s);
   Tile();
   Tile(Tile const &other);
   

   //Getters
   Shape getShape();
   Colour getColour();
   std::string getTileCode();

   void printTileDetails();

   //Setters
   void setShape(Shape s);
   void setColour(Colour c);

   void convertFromCode(char c, int s);

   //Compare tiles
   bool isSameColour(Tile t);
   bool isSameShape(Tile t);
   bool isSameTile(Tile* t);

private:
   Colour colour;
   Shape  shape;
};

#endif // ASSIGN2_TILE_H
