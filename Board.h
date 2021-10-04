
#ifndef BOARD_H
#define BOARD_H

#include "Square.h"

#include<vector>

#define MAX_ROW     26
#define MAX_COL     26
#define INIT_SCORE  0

class Board {
public:
    //Constructor
    Board();
    //Deconstructor
    ~Board();

    //For game play
    void printBoard();
    void initiateBoard();
    Square* getSquare(int row, int col);
    void placeTile(Coord* coord);
    std::string getBoardAsString();


    // Move Validation
    bool moveChecker(Colour colour, Shape shape, Coord* coord);
    //bool tileValid(char colour, int shape);
    bool squareValid(int row, int col);
    //bool lineValid(Colour colour, Shape shape, Coord* coord);

    bool addingToGrid(Square* square, int row, int col);
    bool hasTileNorth(Coord* coord);
    bool hasTileSouth(Coord* coord);
    bool hasTileEast(Coord* coord);
    bool hasTileWest(Coord* coord);

    bool allLinesMatch(Tile* tile, Coord* coord);
    bool northLine(Tile* tile, Coord* coord);
    bool southLine(Tile* tile, Coord* coord);
    bool eastLine(Tile* tile, Coord* coord);
    bool westLine(Tile* tile, Coord* coord);
    
    int getMoveScore();
    void firstMoveMade();

private:
    //Board - 2D Vector
    std::vector<std::vector<Square*>> board;

    //To instantiate square obj 
    std::string initStr  = "   ";
    
    bool hasFirstTile;
    Coord* boardCo = new Coord(0, 0);

    //Score trackers
    int scoreNorth;
    int scoreSouth;
    int scoreEast;
    int scoreWest;
    bool qwirkle;
};

#endif