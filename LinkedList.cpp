
#include "LinkedList.h"

#include <iostream>

LinkedList::LinkedList(){
    Node *head;
    head = NULL;
    this->head = head;
}

LinkedList::~LinkedList() {
   clear();
}

int LinkedList::size() {
   int length = 0;

    Node* current = head;
    while(current != nullptr){
        ++length;
        current = current->next;
    }
    return length;
}

Tile* LinkedList::getTile(int index) {
   //int returnInt = 0;
   Tile* returnTile = new Tile();

    if(index >= 0 && index < size()){

        int counter = 0;
        Node* current = head;

        while(counter<index){
            ++counter;
            current = current->next;
        }

        returnTile = current->tile;

    }else{
        std::cout << "Error: Out of bounds" << std::endl;
    }

    return returnTile;
}

void LinkedList::addFront(Tile* tile){
    // Allocate the node
    Node *newnode = new Node(tile, NULL);
    // Make next of the node as head;
    newnode->next = this->head;
    // Update the head;
    this->head = newnode;
}

void LinkedList::addBack(Tile* tile){
    // Allocate the node
    Node *newnode = new Node(tile, NULL);
    // Define the cur node
    Node *cur = this->head;
    // If the list is empty
    if (this->head == NULL){
        head = newnode;
        return;
    }
    // Find the last node
    while (cur->next != NULL){
        cur = cur->next;
    }
    // Update the last node
    cur->next = newnode;
}
 void LinkedList::addAt(int index, Tile* tile){
     Node* newNode = new Node(tile, NULL);
     Node* cur = this->head;

     if(index == 0){
         addFront(tile);
     } 
     if (index < 0 || index > size() + 1){
         std::cout << "Invalid Postion" << std::endl;
     }
     
     Node* prev = NULL;
     int count = 0;

     while(count < index){
         prev = cur;
         cur = cur->next;

         if( cur == NULL){
            break;
         }
         count++;
       
     }
     newNode->next = cur;
     prev->next = newNode;    
     
        

 }

void LinkedList::deleteFront() {
   if(head != nullptr){
        Node* toDelete = head;
        head = head->next;

        delete toDelete;
    }else{
        throw std::runtime_error("Nothing to remove");
    }
}

void LinkedList::deleteBack() {
   if(head != nullptr){
        Node* current = head;
        Node* prev = nullptr;

        while(current->next != nullptr){
            prev = current;
            current = current->next;
        }

        if(prev == nullptr){
            head = nullptr;
        }else{
            prev->next = nullptr;
        }
        delete current;
    }
}

void LinkedList::deleteAt(int index){
    if(index == 0){
        deleteFront();
    }
    else if(index == size() - 1){
        deleteBack();
    }else{
        Node* current = head;
        Node* beforeNode = nullptr;
        int counter = 0;
        while(counter < index){
            beforeNode = current;
            current = current->next;
            counter++;
        }
        
        // std::cout << "beforeTile:";
        // beforeNode->tile->printTileDetails();
        // std::cout << std::endl;
        // std::cout << "beforeTile next:";
        // beforeNode->next->tile->printTileDetails();
        // std::cout << std::endl;
        // std::cout << "currentTile:";
        // current->tile->printTileDetails();
        // std::cout << std::endl;
        // std::cout << "currentTile next:";
        // current->next->tile->printTileDetails();
        // std::cout << std::endl;

        beforeNode->next = current->next;
        delete current;
    }
}

void LinkedList::clear(){
    Node* next;
    Node* current = head;

    while (current!= nullptr) {
        next = current->next;
        delete current;
        current = next;
    }
}

/*
// Was used for testing.
void LinkedList::printList(){
    Node* first = new Node(this->head->tile, this->head->next);
    //or change to NULL
    while(first != nullptr){
        // readable 
        if(first->next != nullptr){
            std::cout << first->tile->getTileCode() << ", ";
        }else{
            std::cout << first->tile->getTileCode() << std::endl;
        }
        std::cout << first->tile->getTileCode() << std::endl;
        first = first->next;
        std::cout << first->tile->getTileCode() << std::endl;
    }
    delete first;
}
*/

std::string LinkedList::getList(){
    Node *first = new Node(this->head->tile, this->head->next);
    std::string list;
    while(first != NULL){
        //readable 
        std::string ScoreString = std::to_string(first->tile->getShape());
        list = list + first->tile->getColour() + ScoreString;
        if (first->next != nullptr) {
            list += ",";
        }
        first = first->next;
    }
    return list;
}
