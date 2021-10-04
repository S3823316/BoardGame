#include "Board.h"
#include "ErrorMessage.h"
#include <iostream>
#include <sstream>

// Constructor 
Board::Board():board (MAX_ROW, std::vector<Square*>(MAX_COL, nullptr)){
    //Other variables need to be added.
    for(size_t i = 0; i < board.size(); i++){
        for(size_t j = 0; j < board[0].size(); j++){
            Square* square = new Square(boardCo);
            board[i][j] = square;
        }
    }
    // Method to set values to squares for display 
    initiateBoard();
    this->hasFirstTile = false;
    scoreNorth = INIT_SCORE;
    scoreSouth = INIT_SCORE;
    scoreEast = INIT_SCORE;
    scoreWest = INIT_SCORE;
    qwirkle = false;

}

// Deconstructor 
Board::~Board(){
    for(int row = 0; row < MAX_ROW; ++row){
        for(int col = 0; col < MAX_COL; ++col){
            if(board[row][col] != nullptr){
                delete board[row][col];
                board[row][col] = nullptr;
            }
        }
    }
}

Square* Board::getSquare(int row, int col){
    return board[row][col];
}

void Board::initiateBoard(){
    char letter = 'A';

    for(size_t row = 0; row < board.size(); row++){
        for(size_t col = 0; col < board[0].size(); col++){
            
            if(row == 0 && col != 0){
                std::stringstream ss;
                if(col < 10){
                    ss << " " << col << " ";   
                }else{
                    ss << col << " ";
                }
                std::string value = ss.str();
                board[row][col]->setValue(value);

            }else if(col == 0 && row != 0){
                std::stringstream ss;
                ss << " " << letter << "|";
                std::string value = ss.str(); 

                board[row][col]->setValue(value);
                letter++; 

            }else if(row == 0 && col == 0){
                board[row][col]->setValue("   ");

            }else{
                board[row][col]->setValue("  |");
            
                Coord* coord = new Coord(row, col);
                board[row][col]->setCoord(coord);
            }       
        }
    }
}

void Board::printBoard() {
    for(size_t row = 0; row < MAX_ROW; row++){
        for(size_t col = 0; col < MAX_COL; col++){
            std::cout << board[row][col]->getValue();
        }
        std::cout << std::endl;
    }
}

void Board::firstMoveMade(){
    this->hasFirstTile = true;
}

void Board::placeTile(Coord* coord) {
    board[coord->getRowAsInt()][coord->getCol()]->setCoord(coord);
    board[coord->getRowAsInt()][coord->getCol()]->setValue(coord->getTile()->getTileCode() + "|");
}

int Board::getMoveScore(){
    int tileScore = 1;
    if((scoreNorth || scoreSouth) && (scoreEast || scoreWest)){
        tileScore++;
    }
    if(qwirkle){
        tileScore = tileScore + 6;
        std::cout << "QWIRKLE!" << std::endl;
    }
    return scoreNorth + scoreSouth + scoreEast + scoreWest + tileScore;
}

// Return true if square selected is valid (empty and apart of grid)
// && line is valid (tile matches colour/shape of vertical and horizontal lines) 
bool Board::moveChecker(Colour colour, Shape shape, Coord* coord){
    bool valid = false;
    Tile* tile = new Tile(colour, shape);

    if(!hasFirstTile){
        valid = true;
        firstMoveMade();
    }else{
        if(squareValid(coord->getRowAsInt(), coord->getCol()) && allLinesMatch(tile, coord)){
            valid = true;
        }
    }
    return valid;
    delete tile;
    tile = nullptr;

}

// Returns true if the Coord is empty (does not already have a tile) &
// the chosenSquare is part of the grid (next to other tiles)
bool Board::squareValid(int row, int col){
    bool valid = false;

    //Square* chosenSquare = new Square();
    //*chosenSquare = *board[row][col];
    //board[row][col]->getCoord()->getTile()->printTileDetails();
    if(board[row][col]->getCoord() == nullptr || board[row][col]->getCoord()->isCoordEmpty()){
        if(addingToGrid(board[row][col],row,col)){
            valid = true;
        }
    }
    return valid;
}

// Tile must be places on grid (not free standing)
// Returns true if there is at least one tile next to that square 
bool Board::addingToGrid(Square* square, int row, int col){
    bool onGrid = false;
    Coord* chosenCoord = new Coord(row,col);

    if(hasTileNorth(chosenCoord) || hasTileSouth(chosenCoord) || 
        hasTileEast(chosenCoord) || hasTileWest(chosenCoord)){
        onGrid = true; 
    }else{
        std::cout << NOT_ON_GRID << std::endl;
    }
    delete chosenCoord;
    return onGrid;
}

// Returns true if coord has tile above 
bool Board::hasTileNorth(Coord* coord){
    bool hasTile = false;
    Coord* target = board[coord->getRowAsInt()-1][coord->getCol()]->getCoord();

    if(!target->isCoordEmpty()){
        hasTile = true;
    }
    return hasTile;
    delete target;
    target = nullptr;
}

// Returns true if coord has tile below 
bool Board::hasTileSouth(Coord* coord){
    bool hasTile = false;
    Coord* target = board[coord->getRowAsInt()+1][coord->getCol()]->getCoord();

    if(!target->isCoordEmpty()){
        hasTile = true;
    }
    return hasTile;
    delete target;
    target = nullptr;
}

// Returns true if coord has tile right
bool Board::hasTileEast(Coord* coord){
    bool hasTile = false;
    Coord* target = board[coord->getRowAsInt()][coord->getCol()+1]->getCoord();

    if(!target->isCoordEmpty()){
        hasTile = true;
    }
    return hasTile;
    delete target;
    target = nullptr;
}

// Returns true if coord has tile left
bool Board::hasTileWest(Coord* coord){
    bool hasTile = false;
    Coord* target = board[coord->getRowAsInt()][coord->getCol()-1]->getCoord();

    if(!target->isCoordEmpty()){
        hasTile = true;
    }
    return hasTile;
    delete target;
    target = nullptr;
}

bool Board::allLinesMatch(Tile* tile, Coord* coord){
    qwirkle = false;
    bool valid = false;
    bool ns = true;
    bool ew = true;

    // Check both vertical sides match 
    if(hasTileNorth(coord) && hasTileSouth(coord)){
        //North tile colour and shape 
        Colour northCol = board[coord->getRowAsInt()-1][coord->getCol()]->getCoord()->getTile()->getColour();
        Shape northSha = board[coord->getRowAsInt()-1][coord->getCol()]->getCoord()->getTile()->getShape();
        //South tile colour and shape
        Colour southCol = board[coord->getRowAsInt()+1][coord->getCol()]->getCoord()->getTile()->getColour();
        Shape southSha = board[coord->getRowAsInt()+1][coord->getCol()]->getCoord()->getTile()->getShape();
        
        if(northCol != southCol && northSha != southSha){
            if(northCol == southCol && northSha == southSha) {    
                ns = false;
            }
        }
    }
    // Check both horizontal sides match
    if(hasTileEast(coord) && hasTileWest(coord)){
        //East tile colour and shape 
        Colour eastCol = board[coord->getRowAsInt()][coord->getCol()+1]->getCoord()->getTile()->getColour();
        Shape eastSha = board[coord->getRowAsInt()][coord->getCol()+1]->getCoord()->getTile()->getShape();
        //West tile colour and shape
        Colour westCol = board[coord->getRowAsInt()][coord->getCol()-1]->getCoord()->getTile()->getColour();
        Shape westSha = board[coord->getRowAsInt()][coord->getCol()-1]->getCoord()->getTile()->getShape();
        
        if(eastCol != westCol && eastSha != westSha){
            if (eastCol == westCol && eastSha == westSha) {
                ew = false;
            }
        }
    }

    if(northLine(tile, coord) && southLine(tile, coord) && 
        eastLine(tile, coord) && westLine(tile, coord) && ns && ew){
        valid = true;
    }

    if((scoreNorth+scoreSouth+1) == 6){
        qwirkle = true;
    }
    else if((scoreEast+scoreWest+1) == 6){
        qwirkle = true;
    }
    return valid;
}

// Returns true if tile matches line above 
bool Board::northLine(Tile* tile, Coord* coord){
    //Reset score
    scoreNorth = INIT_SCORE;
    bool validCol = true;
    bool validSha = true;
    Colour tileCol = tile->getColour();
    Shape tileSha = tile->getShape();

    for(int i = coord->getRowAsInt()-1; i > 0; i--){
        if(!board[i][coord->getCol()]->getCoord()->isCoordEmpty()){

            Colour colour = board[i][coord->getCol()]->getCoord()->getTile()->getColour();
            Shape shape = board[i][coord->getCol()]->getCoord()->getTile()->getShape();
            if(tileCol != colour){
                validCol = false;
            }
            if(tileSha != shape){
                validSha = false;
            }
            if(tileSha == shape && tileCol == colour) {
                validCol = false;
                validSha = false;
            }
            scoreNorth++;
        }else{
            return (validSha || validCol);
        }
    } 
    return (validSha || validCol);
}

// Returns true if tile matches line below 
bool Board::southLine(Tile* tile, Coord* coord){
    //Reset score
    scoreSouth = INIT_SCORE;
    bool validCol = true;
    bool validSha = true;
    Colour tileCol = tile->getColour();
    Shape tileSha = tile->getShape();

    for(int i = coord->getRowAsInt()+1; i < MAX_ROW; i++){
        if(!board[i][coord->getCol()]->getCoord()->isCoordEmpty()){

            Colour colour = board[i][coord->getCol()]->getCoord()->getTile()->getColour();
            Shape shape = board[i][coord->getCol()]->getCoord()->getTile()->getShape();
            if(tileCol != colour){
                validCol = false;
            }
            if(tileSha != shape){
                validSha = false;
            }
            if(tileSha == shape && tileCol == colour) {
                validCol = false;
                validSha = false;
            }
            scoreSouth++;
        }else{
            return (validSha || validCol);
        }
    } 
    return (validSha || validCol);
}

// Returns true if tile matches line right
bool Board::eastLine(Tile* tile, Coord* coord){
    //Reset score
    scoreEast = INIT_SCORE;
    bool validCol = true;
    bool validSha = true;
    Colour tileCol = tile->getColour();
    Shape tileSha = tile->getShape();

    for(int i = coord->getCol()+1; i < MAX_COL; i++){
        if(!board[coord->getRowAsInt()][i]->getCoord()->isCoordEmpty()){

            Colour colour = board[coord->getRowAsInt()][i]->getCoord()->getTile()->getColour();
            Shape shape = board[coord->getRowAsInt()][i]->getCoord()->getTile()->getShape();
            if(tileCol != colour){
                validCol = false;
            }
            if(tileSha != shape){
                validSha = false;
            }
            if(tileSha == shape && tileCol == colour) {
                validCol = false;
                validSha = false;
            }
            scoreEast++;
        }else{
            return (validSha || validCol);
        }
    } 
    return (validSha || validCol);
}

// Returns true if tile matches line left 
bool Board::westLine(Tile* tile, Coord* coord){
    //Reset score
    scoreWest = INIT_SCORE;
    bool validCol = true;
    bool validSha = true;
    Colour tileCol = tile->getColour();
    Shape tileSha = tile->getShape();

    for(int i = coord->getCol()-1; i > 0; i--){
        if(!board[coord->getRowAsInt()][i]->getCoord()->isCoordEmpty()){
            Colour colour = board[coord->getRowAsInt()][i]->getCoord()->getTile()->getColour();
            Shape shape = board[coord->getRowAsInt()][i]->getCoord()->getTile()->getShape();
            if(tileCol != colour){
                validCol = false;
            }
            if(tileSha != shape){
                validSha = false;
            }
            if(tileSha == shape && tileCol == colour) {
                validCol = false;
                validSha = false;
            }
            scoreWest++;
        }else{
            return (validSha || validCol);
        }
    } 
    return (validSha || validCol);
}

std::string Board::getBoardAsString(){
    std::string boardString; 
    std::string rowString;

    bool firstTile = false;

    for(int row = 1; row < MAX_ROW; row++){
        for(int col = 1; col < MAX_COL; col++){

            if(!board[row][col]->getCoord()->isCoordEmpty()) {

                rowString = board[row][col]->getCoord()->getTile()->getTileCode();
                rowString += "@";
                rowString += board[row][col]->getCoord()->getRow();
                rowString.append(std::to_string(board[row][col]->getCoord()->getCol()));

                if (firstTile == true) {
                    boardString += "," + rowString;
                } else {
                    boardString += rowString;
                    firstTile = true;
                }
            }
        }
    }
    return boardString;

}