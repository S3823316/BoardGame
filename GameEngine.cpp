#include "GameEngine.h"
#include <iostream>
#include <fstream>
#include <regex>
#include <string.h>


GameEngine::GameEngine(){
    this->board = new Board();
    this->tileBag = new TileBag();
}

GameEngine::~GameEngine(){
   delete board;
   delete tileBag;
   delete player1;
   delete player2;
}

void GameEngine::defineSeed(){
    tileBag->setSeed(3343562680);
}


Board* GameEngine::getBoard(){
    return this->board;
}

void GameEngine::startNewGame(){ 
    player1sTurn = true;
    std::string input;
    bool prompt = true;

    std::cout << "Starting a New Game" << std::endl;

     do {
        if(prompt){
            std::cout << "Enter a name for player 1 (uppercase characters only):" << std::endl;

            std::cin.ignore();
            std::cout << USER_PROMPT;
            
            std::getline(std::cin, input);

            prompt = false;
        }
       if((!validateName(input))){
            if (std::cin.eof()) {
                std::cout << "GoodBye!" << std::endl;
                exit(0);
            }
            std::cout << WRONG_NAME_FORMAT << std::endl;
            
            std::cout << USER_PROMPT;
            std::getline(std::cin, input);
            }
            player1 = new Player(input);
    }while(!validateName(input));
    
    prompt = true;
    do {
        if(prompt){
            std::cout << "Enter a name for player 2 (uppercase characters only):" << std::endl;
            std::cout << USER_PROMPT;
            //std::cin.ignore();
            std::getline(std::cin, input);

            prompt = false;
        }
        if((!validateName(input))){
            if (std::cin.eof()) {
                std::cout << "GoodBye!" << std::endl;
                exit(0);
            }
            std::cout << WRONG_NAME_FORMAT << std::endl;
            
            std::cout << USER_PROMPT;
            std::getline(std::cin, input);
    }
    player2 = new Player(input);
    }while(!validateName(input));

    std::cout << "Let's Play!" << std::endl;
    playGame();

    /*
    // For testing ----------------------------------
    std::cout << "Player 1: " << player1->getPlayerName() << std::endl;
    std::cout << "Player 2: " << player2->getPlayerName() << std::endl;
    */
}

void GameEngine::playGame(){
    if (tileBag->getTileBagSize() == 0) {
        tileBag->generateTiles();
        dealPlayerHand(player1);
        dealPlayerHand(player2); 
    }

    // Game ends once a player has no tiles left in hand 
    while(player1->getPlayerHandSize() != 0 && player2->getPlayerHandSize() != 0){
        if(player1sTurn){

            playerTurn(player1);
            //std::cout << "p1 turn complete" <<std::endl;
            player1sTurn=false;
        }else{
            playerTurn(player2);
            //std::cout << "p2 turn complete" <<std::endl;
            player1sTurn=true;
        }
    }
}

void GameEngine::dealPlayerHand(Player* player){
    for(int i = player->getPlayerHandSize(); i < HAND_SIZE; i++){
        if(tileBag->getTileBagSize() > 0){
            player->addToPlayerHand(tileBag->drawTile());
        }
    }   
}

void GameEngine::playerTurn(Player* player){
    bool moveComplete = false;
    bool commandAccepted = false;
    Tile* userTile = new Tile();
    Coord* userCoord = new Coord(-1, -1);
    std::string command = "";
    player->toggleTurn();
    
    board->printBoard();
    std::cout << player->getPlayerName() << ", it's your turn!" << std::endl;
    printScores();
    std::cout << "Your hand: ";
    player->printPlayerHand();

    while(!moveComplete){
        // Get input from player 
        userInput = "";  
        std::cout << USER_PROMPT;
        std::getline(std::cin, userInput);

        if (std::cin.eof()) {
            std::cout << "GoodBye!" << std::endl;
            exit(0);
        }

        // Get command type     
        if(extractCommandType(userInput) != INVALID_INPUT){
            commandAccepted = true;
            command = extractCommandType(userInput);
        }else{
            std::cout << INVALID_INPUT << std::endl;
        }

        if(commandAccepted){
            if(command == "place"){
                bool validInput = true;
                try{
                    *userCoord = *extractCoordFromInput(userInput);
                    *userTile = *extractTileFromInput(userInput);
                    if(userCoord->getCol() == 0 || userCoord->getRow() == 0){
                        std::cout << INVALID_INPUT <<std::endl;
                        validInput = false;
                    }
                }catch(const std::exception& ex){
                    std::cout << INVALID_INPUT <<std::endl;
                    validInput = false;
                }
                
                if(validInput){
                    if(player->playerHasTile(userTile)){
                        userCoord->setTile(userTile);
                        if(board->moveChecker(userTile->getColour(), userTile->getShape(), userCoord)){
                            board->placeTile(userCoord);
                            player->removeTile(userTile);
                            player->addToPlayerHand(tileBag->drawTile());
                            //Set player score after successful move 
                            player->setScore(player->getScore()+board->getMoveScore());
                            moveComplete = true;
                        }else{
                            std::cout << INVALID_MOVE << std::endl;
                        }
                    }else{
                        std::cout << INVALID_TILE << std::endl;
                    }
                }

            }else if(command == "replace"){
                bool validTile = true;

                try{
                    *userTile = *extractTileFromInput(userInput);
                }catch(const std::exception& ex){
                    std::cout << INVALID_INPUT <<std::endl;
                    validTile = false;
                }

                // If valid tile - implement replacing tile
                if(validTile){ 
                    if(player->playerHasTile(userTile)){
                        int index = player->indexOfTile(extractTileFromInput(userInput));
                        // Add removed to back of tilebag
                        tileBag->addTile(player->getTile(index));
                        // Remove from hand
                        player->removeTile(player->getTile(index));
                        // Add from tileBag to hand 
                        player->addToPlayerHand(tileBag->drawTile());
                        moveComplete = true;
                    }else{
                        std::cout << INVALID_TILE <<std::endl;
                    }
                }

            }else if(command == "save"){
                //std::cout << "SAVE" <<std::endl;
                saveGame(extractFileFromInput(userInput));
                playerTurn(player);
                moveComplete = true;

            }else if(command == "^D"){
                std::cout << "Goodbye!" << std::endl; 
                exit(0);
            }
        }
    }
    
    userTile = nullptr;
    userCoord = nullptr;

    player->toggleTurn();
}

void GameEngine::printScores(){
    std::cout << "Score for "<< player1->getPlayerName() << ": " << player1->getScore() << std::endl;
    std::cout << "Score for "<< player2->getPlayerName() << ": " << player2->getScore() << std::endl;
}

// Get first word of user input 
std::string GameEngine::extractCommandType(std::string input){
    const char* delimiter = " ";
    int index1 = input.find_first_of(delimiter);
    std::string returnStr = input.substr(0, index1);

    if(!(returnStr == "place" || returnStr == "replace" || returnStr == "save" || returnStr == "^D")){
        returnStr = INVALID_INPUT;
    }
    return returnStr;
}

Tile* GameEngine::extractTileFromInput(std::string input){
    // For place and replace command
    const char* delimiter = " ";
    // Should come back after first word.
    int index = input.find_first_of(delimiter);
    

    char tileColour = input[index+1];
    std::string tileShape = input.substr(index+2, 1);
    int x = std::stoi(tileShape);
 

    Tile* returnTile = new Tile();
    returnTile->convertFromCode(tileColour, x);
    //Testing---------------------------------
    //std::cout <<  << std::endl;
    //returnTile->printTileDetails();
    
    return returnTile;
    delete returnTile;
}

std::string GameEngine::extractFileFromInput(std::string input){
    std::cout << input << std::endl;
    const char* delimiter = " ";
    int index = input.find_first_of(delimiter);
    std::string save = input.substr(0, index);
    std::string sub = input.substr(index+1, input.length() - save.length());

    return sub;
}

Coord* GameEngine::extractCoordFromInput(std::string input){
    // Only for place command.
    // Index 12 and 13/14. 
    Coord* returnCoord = new Coord(0, 0);

    char row = input[12];
    int coordRow = 0; 
    if(isupper(row)){
        coordRow = row-'A'+1;
    }
    std::string col = input.substr(13);
    int coordCol = 0;

    try{
        //Convert std::string to int
        std::stringstream ss;
        ss << col;
        ss >> coordCol;

    }catch(const std::exception& ex){
        std::cout<<INVALID_INPUT<<std::endl;
    }

    if(coordRow != 0 && coordCol != 0){
        returnCoord->setPos(coordRow, coordCol);
    }else{
        returnCoord->setPos(0, 0);
    }

    return returnCoord;
}

bool GameEngine::validateName(std::string& playerName){
    bool validation = false;
   
    std::regex name("[A-Z]{1,25}");  
    if(std::regex_match(playerName, name)){
        validation = true;
    }
    return validation;
}

void GameEngine::loadGame(std::string filename) {
    std::string line;
    std::ifstream save(filename);
    
    bool player1Data = false;
    bool playerData = false;

    bool name = false;
    bool score = false;
    bool hand = false;

    bool currentShape = false;
    bool currentState = false;
    bool currentTileBag = false;
    bool currentTurn = false;

    if (save.is_open()){
        for (int i = 0; i < SAVE_LENGTH; i++){
            getline(save,line);
            //std::cout << "line: " << i << std::endl;

            if(player1Data == false) {
                if (name == false) {
                    player1 = new Player(line);
                    name = true;
                    //std::cout << "name set: " + player1->getPlayerName() << std::endl; 

                } else if (score == false) {
                    player1->setScore(std::stoi(line));
                    score = true;
                    //std::cout << "score set: " <<player1->getScore() << std::endl; 

                } else if (hand == false) {
                    loadHand(player1, line);
                    player1Data = true;
                    name = false;
                    score = false;

                    //std::cout << "hand set "; 
                    //player1->printPlayerHand();
                }

            } else if (playerData == false) {
                if (name == false) {
                    player2 = new Player(line);
                    name = true;
                    //std::cout << "name set: " + player2->getPlayerName() << std::endl;

                } else if (score == false) {
                    player2->setScore(std::stoi(line));
                    score = true;
                    //std::cout << "score set: " << player2->getScore() << std::endl; 

                } else if (hand == false) {
                    loadHand(player2, line);

                    //std::cout << "hand set "; 
                    //player2->printPlayerHand();

                    playerData = true;
                }

            } else if (playerData == true && currentShape == false) {
                // Not implemented for this milestone
                //std::cout << "shape set" << std::endl; 
                currentShape = true;

            } else if (playerData == true && currentState == false) {
                
                int number;
                int length = 0;
                char character;

                int col = 0;
                char row = 0;

                std::vector<std::string> placedTiles;

                while(line[length] != 0) {
                    length++;
                }

                for (int i = 0; i < length; i++) {
                    character = line[i];
                    number = (int)line[i + 1] - 48;
                    
                    Tile* tile = new Tile();
                    tile->convertFromCode(character, number);
                    
                    row = line[i + 3];
                    col = (int)line[i + 4] - 48;

                    // std::cout << "char:" << character << " num:" << number << " i:" << i << std::endl;
                    // std::cout << "@| char:" << row << " col: " << col << std::endl;
                    // std::cout << "coord num: " << (int)row << " || " << (int)row - 65 << std::endl;
                    // std::cout << "----------------" << std::endl;

                    Coord* coord = new Coord((int)row - 64, col, tile);
                    board->placeTile(coord);
                    
                    i += 5;
                }
                
                //std::cout << "state set" << std::endl;
                currentState = true;

            } else if (playerData == true && currentTileBag == false) {
                
                int number;
                int length = 0;
                char character;

                while(line[length] != 0) {
                    //std::cout << length << ": " << line[length] << std::endl;
                    length++;
                }
                //std::cout << length << std::endl;

                for (int i = 0; i < length; i++) {
                    character = line[i];
                    number = (int)(line[i + 1]) -48;
                    Tile* tile = new Tile();
                    tile->convertFromCode(character, number);
                    tileBag->addTile(tile);

                    i += 2;
                }
                // tileBag->printTileBag();
                // std::cout << "tilebag set" << std::endl;
                currentTileBag = true;

            } else if (playerData == true && currentTurn == false) {
                //std::cout << "turn set" << std::endl;
                currentTurn = true;
            }
            // To print savefile:
            //std::cout << line << '\n';
        }
        save.close();
    }
    // std::cout << "done, printing hands: " << std::endl;
    // std::cout << "Player 1:" << std::endl;
    // player1->printPlayerHand();
    // std::cout << "Player 2:" << std::endl;
    // player2->printPlayerHand();
    
    //board->printBoard();
    playGame();
}

void GameEngine::saveGame(std::string input){


    std::ofstream MyFile(input + ".save");

    MyFile << player1->getPlayerName();

    MyFile << "\n" << player1->getScore();

    MyFile << "\n" << player1->getPlayerHand();

    MyFile << "\n" << player2->getPlayerName();

    MyFile << "\n" << player2->getScore();

    MyFile << "\n" << player2->getPlayerHand();
    
    // Currently a static value
    MyFile << "\n" << "26,26";

    MyFile << "\n" << board->getBoardAsString();

    MyFile << "\n" << tileBag->getTileBag();

    if(player1->getTurn()){
        MyFile << "\n" << player1->getPlayerName();
    } else
    {
        MyFile << "\n" << player2->getPlayerName();
    }

}

void GameEngine::loadHand(Player* player, std::string hand) {
    int number;
    int length = 0;
    char character;

    //std::cout << hand << std::endl;

    while(hand[length] != 0) {
        //std::cout << length << ": " << line[length] << std::endl;
        length++;
    }
    //std::cout << length << std::endl;

    for (int i = 0; i < length; i++) {
        character = hand[i];
        number = (int)(hand[i + 1]) -48;

        //std::cout << "char:" << character << " num:" << number << " i:" << i << std::endl;

        Tile* tile = new Tile();
        tile->convertFromCode(character, number);
        player->addToPlayerHand(tile);

        i += 2;
    }
}
