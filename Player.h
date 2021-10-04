#ifndef PLAYER_H
#define PLAYER_H

#include "LinkedList.h"
#include "Tile.h"
#include <iostream>

#define HAND_SIZE  6

class Player {
public:
    Player(std::string name);
    ~Player();
    int getScore();
    std::string getPlayerName(); 
    Tile* getTile(int index);    

    void addToPlayerHand(Tile* tile);
    void printPlayerHand();
    int getPlayerHandSize();
    std::string getPlayerHand();
    std::string getList();
    bool playerHasTile(Tile* tile);
    int indexOfTile(Tile* tile);

    void setScore(int s);
    void setName(std::string n);
    bool getTurn();
    void toggleTurn();
    void removeTile(Tile* tile);

private:
    int playerScore; 
    std::string playerName;
    LinkedList* playerHand;
    bool turn; 
};
#endif
 