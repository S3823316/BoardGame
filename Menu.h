#ifndef MENU_H
#define MENU_H

#include <string>
#include <iostream>
#include "GameEngine.h"
#include "LinkedList.h"

class Menu {
public:
    void runGame();
    void loadGame();
    //void startNewGame();
    void printMenu();
    void showCredits();
    bool checkFileExist(std::string fileName);
  //  bool validateName(std::string& playerName);
    std::string convertStringToUpper(std::string input);

private:
    GameEngine* game;
};

#endif