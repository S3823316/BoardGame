
#include "Menu.h"
#include "ErrorMessage.h"
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cctype>
#include <regex>
#include <fstream>

void Menu::runGame(){
    std::cout << "\033[1;31mW\033[0m"  
      << "\033[1;32mE\033[0m" 
      << "\033[1;33mL\033[0m" 
      << "\033[1;34mC\033[0m" 
      << "\033[1;35mO\033[0m" 
      << "\033[1;36mM\033[0m" 
      << "\033[1;37mE\033[0m" <<  " " 
      << "\033[1;32mT\033[0m"  
      << "\033[1;33mO\033[0m" << " "
      << "\033[1;34mQ\033[0m"
      << "\033[1;35mW\033[0m"
      << "\033[1;36mI\033[0m"
      << "\033[1;37mR\033[0m"
      << "\033[1;32mK\033[0m"
      << "\033[1;33mL\033[0m"
      << "\033[1;34mE\033[0m"
      << "\n-----------------"
      << std::endl;

      //players needed here
      //game = new GameEngine();
      printMenu();
}

void Menu::printMenu(){
   std::cout << "Menu" << std::endl; 
   std::cout << "----" << std::endl;
   std::cout << "1. New Game" << std::endl;
   std::cout << "2. Load Game" << std::endl; 
   std::cout << "3. Credits (Show student information)" << std::endl; 
   std::cout << "4. Quit" << std::endl; 

    std::string userInput = "";
    std::cout << USER_PROMPT;
    if (std::cin.eof()) {
        std::cout << "GoodBye!" << std::endl;
        exit(0);
    }
    std::cin >> userInput;
    if(userInput == "1"){
        //Moved to only create new Game if 1 is selected.
        game = new GameEngine();
        game->startNewGame();
    } else if(userInput == "2"){
        game = new GameEngine();
        loadGame();
    } else if (userInput == "3"){
        showCredits();
    } else if (userInput == "4"){
        std::cout << "GoodBye!" << std::endl;
        // Exit successfully
        exit(0);
    } else if(userInput == "^D"){
        std::cout << "GoodBye!" << std::endl;
    }
    else if(userInput == "5"){
        game = new GameEngine();
        game->defineSeed();
        game->startNewGame();
    }else{
        std::cout << INVALID_INPUT << std::endl;
        std::cout << userInput << std::endl;
        // Review
        printMenu();
    }
}

void Menu::loadGame(){
    std::string filename = "";
    std::cout << "\nEnter the filename of the game you would like to load"
              << std::endl;
    
    do {
        std::cin >> filename;
    
    if (std::cin.eof()) {
        std::cout << "GoodBye!" << std::endl;
        exit(0);
    }
    if (!checkFileExist(filename)) {
        std::cout << NO_FILE_EXIST << std::endl;
    }
    } while(!checkFileExist(filename));

    game->loadGame(filename);
}
 
 bool Menu::checkFileExist(std::string fileName){
     std::ifstream fileExist(fileName.c_str());
     return (bool)fileExist;
 }

 void Menu::showCredits(){
      std::cout << "--------------------------------------------"
          << "\n\033[1;31mName: Anna Mance\033[0m"
          << "\n\033[1;31mStudent ID: 3776120\033[0m"
          << "\n\033[1;31mEmail: s3776120@student.rmit.edu.au\033[0m"
          << "\n\n\033[1;32mName: Lachlan Sexton\033[0m"
          << "\n\033[1;32mStudent ID: 3839908\033[0m"
          << "\n\033[1;32mEmail: s3839908@student.rmit.edu.au\033[0m"
          << "\n\n\033[1;33mName: Allen M Jose\033[0m"
          << "\n\033[1;33mStudent ID: 3823316\033[0m"
          << "\n\033[1;33mEmail: s3823316@student.rmit.edu.au\033[0m"
          << "\n\n\033[1;34mName: Nikita Zaytsev\033[0m"
          << "\n\033[1;34mStudent ID: 3838806\033[0m"
          << "\n\033[1;34mEmail: 3838806@student.rmit.edu.au\033[0m"
          << "\n--------------------------------------------" 
          << std::endl;

          printMenu();

 }
