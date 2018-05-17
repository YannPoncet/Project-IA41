#ifndef GAME_H
#define GAME_H

#include<iostream>

#include "../view/gameFrame.cpp"
#include "Plateau.cpp"

using namespace std;

class Game {
  private:
    int phase; //Phase of the game (actually 1 for menus, 2 for pawn placement, 3 for pawn movements, 4 for victory screen ?)
    int turn; //Indicates which player is playing
    void GameLoop();
    GameFrame* gameFrame;
    Plateau* plateau;
    void loop();
    vector<int> gameState; //[0]Player1: 0=AI,1=Human ; [1]Player2: 0=AI,1=Human ; [2]Start: 0=No,1=Yes

  public:
    Game();
    ~Game(){};

    void start();
    void switchTurn();
    bool isItAt1From(int x1, int x2, int y1, int y2);
};

#endif
