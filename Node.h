#ifndef NODE_h
#define NODE_h

#include "Tile.h"

class Node {
public:

   Node(Tile* tile, Node* next);
   Node(Node& other);
   ~Node();

   Tile*  tile;
   Node*  next;
};
#endif
 