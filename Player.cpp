#include "Player.h"
#include "ErrorMessage.h"
#include <iostream>


Player::Player(std::string name){
    playerName = name; 
    playerHand = new LinkedList;
    turn = false;
}

Player::~Player(){
    delete playerHand;
}

int Player::getScore(){
    return playerScore;
}

void Player::addToPlayerHand(Tile* tile){
    this->playerHand->addBack(tile);
}

int Player::getPlayerHandSize(){
    return playerHand->size();
}

std::string Player::getPlayerName(){
    return playerName;
}

// Used in place and replace functionality 
bool Player::playerHasTile(Tile* tile){
    bool hasTile = false;
    for(int i = 0; i < getPlayerHandSize(); i++){
        if(playerHand->getTile(i)->isSameTile(tile)){
            hasTile = true;
        }
    }
    return hasTile;
}

int Player::indexOfTile(Tile* tile){
    int index = -1;
    for(int i = 0; i < playerHand->size(); i++){
        if(playerHand->getTile(i)->isSameTile(tile)){
            index = i;
        }
    }
    return index;
}

Tile* Player::getTile(int index){
    return playerHand->getTile(index);
}

// Used in playerTurn
void Player::printPlayerHand(){
    for(int i = 0; i < HAND_SIZE; i++){
        if(playerHand->getTile(i) != nullptr){
            if(playerHand->getTile(i) != nullptr && i < HAND_SIZE-1){
                playerHand->getTile(i)->printTileDetails();
                std::cout << ", ";
            }else if(playerHand->getTile(i) != nullptr && i == HAND_SIZE-1){
                playerHand->getTile(i)->printTileDetails();
                std::cout << std::endl;
            }
        }else{
            std::cout << NULLPTR_TILE << std::endl;
        }
    }
}

void Player::setScore(int s) {
    playerScore = s;
}

void Player::setName(std::string n) {
    playerName = n;
}

std::string Player::getPlayerHand(){
    return playerHand->getList();
}

bool Player::getTurn(){
    if(turn){
        return true;
    }
    else{
        return false;
    }   
}

void Player::toggleTurn(){
    if(turn){
        turn = false;
    }else{
        turn = true; 
    }
}

void Player::removeTile(Tile* tile){
    playerHand->deleteAt(indexOfTile(tile));
}

