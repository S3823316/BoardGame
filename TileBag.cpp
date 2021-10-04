#include "TileBag.h"
#include "TileCodes.h"
#include "Tile.h"
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
// Constructor
TileBag::TileBag(){
    tileBag = new LinkedList();
}

// Deconstructor
TileBag::~TileBag(){
    delete tileBag;
}

void TileBag::setSeed(unsigned seed){
    this->seed = seed;
}

int TileBag::getTileBagSize(){
    return tileBag->size();
}

// Generate Tile Bag Filled with each type of tile
// IS NOT MIXED

void TileBag::generateTiles(){
    int repeats = 2;
    char colours [NO_DIFF] = {RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE};
    int shapes [NO_DIFF] = {CIRCLE, STAR_4, DIAMOND, SQUARE, STAR_6, CLOVER};
    std::vector<Tile*> inOrder{};

    if(seed == 1){
        seed = std::chrono::system_clock::now().time_since_epoch().count();
    }

    std::default_random_engine e(seed);
    

    //added to make it 2 times the tiles
    for(int k = 0; k < repeats; k++){
        for(int i = 0; i < NO_DIFF; ++i){
            for(int j = 0; j < NO_DIFF; ++j){
                Tile* tile = new Tile(colours[i], shapes[j]);
                inOrder.push_back(tile);
            }
        }
    }

    std::shuffle(std::begin(inOrder),std::end(inOrder),e);

    for(int x = 0; x < 71; x++){
        tileBag->addFront(inOrder[x]);
    }
}

//For testing
void TileBag::printTileBag(){
    for(int i = 0; i < tileBag->size(); i++){
        tileBag->getTile(i)->printTileDetails();
        //std::cout << std::endl;
    }
}

std::string TileBag::getTileBag(){
    return tileBag->getList();
}

// Returns a tile that has been removed from front of tileBag
Tile* TileBag::drawTile(){
    Tile* drawnTile = new Tile();

    if(tileBag->getTile(0) != nullptr){
        *drawnTile = *tileBag->getTile(0);
    }else{
        std::cout << "Tile bag is empty. Cannot draw." << std::endl;
    }

    tileBag->deleteFront();
    return drawnTile;
    delete drawnTile;
}

void TileBag::addTile(Tile* tile) {
    tileBag->addBack(tile);
}
