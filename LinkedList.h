#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"
#include "Node.h"

class LinkedList {
public:
   LinkedList();
   ~LinkedList();
   
   int size();
   void clear();
   Tile* getTile(int index);

   //void printList();
   std::string getList();
   int indexOf(Tile* tile);

   void addFront(Tile* tile);
   void addBack(Tile* tile);
   void addAt(int index, Tile* tile);

   void deleteFront();
   void deleteBack();
   void deleteAt(int index);

private:
   Node* head;
};

#endif