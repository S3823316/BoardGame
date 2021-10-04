
#include "Tile.h"
#include <iostream>


Tile::Tile(Colour c, Shape s){
    this->colour = c;
    this->shape = s;
}

Tile::Tile(){
    this->colour = DEF_COL;
    this->shape = DEF_SHA;
}

Tile::Tile(Tile const &other){
    this->colour = other.colour;
    this->shape = other.colour;
}

// GETTERS
Shape Tile::getShape(){
    return shape;
}

Colour Tile::getColour(){
    return colour;
}

std::string Tile::getTileCode() {
    std::string code;
    code.append(1,this->getColour());
    std::string s = std::to_string(this->getShape());
    return code + s;
}

// Used in printPlayerHand & printTileBag
void Tile::printTileDetails() {
    if(this->colour != DEF_COL && this->shape != DEF_SHA){
        std::cout << (char)this->colour << (int)this->shape;
    }else{
        std::cout << "Default tile";
    }
}

// SETTERS
void Tile::setShape(Shape s){
    shape = s;
}

void Tile::setColour(Colour c){
    colour = c;
}

void Tile::convertFromCode(char c, int s){
    // Set colour 
    if(c == RED){
        this->colour = RED;
    }else if(c == ORANGE){
        this->colour = ORANGE;
    }else if(c == YELLOW){
        this->colour = YELLOW;
    }else if(c == GREEN){
        this->colour = GREEN;
    }else if(c == BLUE){
        this->colour = BLUE;
    }else if(c == PURPLE){
        this->colour = PURPLE;
    }else{
        this->colour = DEF_COL;
    }
    // Set shape
    if (s == CIRCLE) {
        this->shape = CIRCLE;
    } else if (s == STAR_4) {
        this->shape = STAR_4;
    } else if (s == DIAMOND) {
        this->shape = DIAMOND;
    } else if (s == SQUARE) {
        this->shape = SQUARE;
    } else if (s == STAR_6) {
        this->shape = STAR_6;
    } else if (s == CLOVER) {
        this->shape = CLOVER;
    } else {
        this-> shape = DEF_SHA;
    }
}

//Comparing Tiles
bool Tile::isSameColour(Tile t){
    return colour == t.colour;
}

bool Tile::isSameShape(Tile t){
    return shape == t.shape;
}

bool Tile::isSameTile(Tile* t){
    bool isSame = false;
    if (this->shape == t->getShape() && this->colour == t->getColour()){
        isSame = true;
    }
    return isSame;
}
