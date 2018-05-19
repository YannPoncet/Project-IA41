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

    /**PlayerType:
    * [0]Player1: 0=Human, 1=Noob AI, 2=Not so bad AI, 3=God AI
    * [1]Player2: 0=Human ,1=Noob AI, 2=Not so bad AI, 3=God AI
    */
    vector<int> playerType;

  public:
    Game();
    ~Game(){};

    void start();
    void switchTurn();
    bool isItAt1From(int x1, int x2, int y1, int y2);
};

#endif
