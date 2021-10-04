#include "Square.h"
#include <sstream>

Square::Square(){
    this->value = "  ";
    this->coord = nullptr;
}

Square::Square(Coord* coord){
    this->coord = coord;
    if(!coord->isCoordEmpty()){
        std::stringstream ss;
        ss << coord->getTile()->getColour() << coord->getTile()->getShape() << "|";
        std::string value = ss.str(); 
        this->value = value;
    }else{
        this->value = "   ";
    }
}

Square::~Square(){
    if(coord != nullptr){
        delete coord;
    }
}

// Getters
std::string Square::getValue(){
    return value;
}

Coord* Square::getCoord(){
    return coord;
}

// Setters
void Square::setValue(std::string v){
    value = v;
}

void Square::setValue(Tile* tile){
    // Value will be 3 char string
    std::stringstream ss;
    ss << tile->getColour() << tile->getShape() << "|";
    std::string value = ss.str(); 
    value = value;
}

void Square::setCoord(Coord* c){
    coord = c;
}