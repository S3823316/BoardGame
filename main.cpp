#include <iostream>

#include "Node.h"
#include "LinkedList.h"
#include "Tile.h"
#include "Board.h"
#include "Player.h"
#include "GameEngine.h"

int main(){

    //Testing new linkedlist implementation

    Tile* t = new Tile(PURPLE, STAR_4);
    Tile* z = new Tile(RED, CIRCLE);
    Tile* y = new Tile(ORANGE, STAR_6);
    Tile* x = new Tile(BLUE, SQUARE);
    LinkedList* llist = new LinkedList();
    llist->addFront(t);
    llist->addFront(y);
    llist->addFront(x);
    llist->addFront(t);
    llist->addAt(2, z);
    //llist->printList();

    std::cout << "Print: " << std::endl;
    (llist->getTile(0))->printTileDetails();
    (llist->getTile(1))->printTileDetails();
    (llist->getTile(2))->printTileDetails();
    (llist->getTile(3))->printTileDetails();
    (llist->getTile(8))->printTileDetails();

    /*Prints addresses of pointers
    std::cout << llist->getTile(0) << std::endl;
    std::cout << llist->getTile(1) << std::endl;
    std::cout << llist->getTile(2) << std::endl;
    std::cout << llist->getTile(3) << std::endl;
    std::cout << llist->getTile(6) << std::endl;
    */

    /*
    std::cout << std::endl;
    llist->deleteFront();
    llist->printList();

    std::cout << std::endl;
    llist->deleteBack();
    llist->deleteAt(1);
    llist->printList();

    std::cout << std::endl;

    //Test Board Class
    std::cout << "The Board: " <<std::endl;
    Board* board = new Board();

    Coord* c1 = new Coord(9,9,t);
    board->placeTile(c1);

    Coord* c2 = new Coord(13,15,z);
    board->placeTile(c2);

    board->printBoard();
    std::cout << board->getBoardAsString() << std::endl;

    //Test TileBag
    TileBag* bag = new TileBag();
    bag->generateTiles();
    */

    //Deal player hand
    /*
    Player* player1 = new Player("P1");
    Player* player2 = new Player("P2");
    GameEngine* ge = new GameEngine(player1, player2);

    ge->getBoard()->printBoard();

    ge->startGame();


*/
    /*
    //Test Move Validation
    Tile* a = new Tile(PURPLE, STAR_6);
    Tile* a2 = new Tile(PURPLE, SQUARE);

    Tile* b = new Tile(ORANGE, CIRCLE);
    Tile* b2 = new Tile(BLUE, CIRCLE);

    Tile* c = new Tile(RED, STAR_4);

    std::cout << std::boolalpha;

    // Before any tiles placed: true
    Coord* ca = new Coord(('J'-'A'+1), 9, a);
    Coord* ca2 = new Coord(('I'-'A'+1), 9, a2);

    Coord* cb = new Coord(('B'-'A'+1), 4, b);
    Coord* cb2 = new Coord(('A'-'A'+1), 4, b2);

    Coord* cc1 = new Coord(('C'-'A'+1), 4, c);
    Coord* cc2 = new Coord(('H'-'A'+1), 9, c);

    bool test = ge->getBoard()->isValidMove(a, 'J', 9);
    std::cout << "Test 1 bool: " << test << std::endl;
    ge->getBoard()->placeTile(ca);

    test = ge->getBoard()->isValidMove(a2, 'K', 9);
    std::cout << "Test 2 bool: " << test << std::endl;
    ge->getBoard()->placeTile(ca2);

    test = ge->getBoard()->isValidMove(b, 'B', 4);
    std::cout << "Test 3 bool: " << test << std::endl;
    ge->getBoard()->placeTile(cb);

    test = ge->getBoard()->isValidMove(b2, 'C', 4);
    std::cout << "Test 4 bool: " << test << std::endl;
    ge->getBoard()->placeTile(cb2);

    ge->getBoard()->printBoard();

    test = ge->getBoard()->isValidMove(c, 'D', 4);
    std::cout << "Test 5 bool: " << test << std::endl;
    ge->getBoard()->placeTile(cc1);

    test = ge->getBoard()->isValidMove(c, 'L', 9);
    std::cout << "Test 6 bool: " << test << std::endl;
    ge->getBoard()->placeTile(cc2);
*/

    //GameEngine* game = new GameEngine();
    //game->loadGame("testSave.txt");

    /*
    Node* head =  NULL;
    Node* second = NULL;
    Node* third = NULL;

    head = new Node();
    second = new Node();
    third = new Node();

    head->data = 1;
    head->next = second;


    second->data = 2;
    second->next = third;

    third->data = 3;
    third->next = NULL;
    */

    delete llist;
    return EXIT_SUCCESS;
}
