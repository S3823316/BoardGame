#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "Player.h"
#include "Board.h"
#include "TileBag.h"
#include "Coord.h"
#include "ErrorMessage.h"
#include <fstream>
#include <iostream>
#include <sstream>

#define SAVE_LENGTH 10

class GameEngine {
public:

    GameEngine();
    ~GameEngine();

    Board* getBoard();

    //void startGame();
    void dealPlayerHands();
    void playerTurn(Player* player, Tile* tile, Coord* coord);
    std::string convertStringToUpper(std::string input);
    void startNewGame();

    void loadGame(std::string filename);
    void loadHand(Player* player, std::string hand);

    void playGame();
    void playerTurn(Player* player);
    
    bool validateName(std::string& playerName);
    void dealPlayerHand(Player* player);
    void printScores();
    void defineSeed();

    std::string extractCommandType(std::string input);
    std::string extractFileFromInput(std::string input);
    Tile* extractTileFromInput(std::string input);
    Coord* extractCoordFromInput(std::string input);

    void saveGame(std::string input);

private:
    Player* player1;
    Player* player2;
    Board* board;
    TileBag* tileBag;
    std::string userInput;
    //Keep track of turns for saved game.
    bool player1sTurn;

};


#endif
