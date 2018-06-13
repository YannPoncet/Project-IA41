#ifndef GAME_H
#define GAME_H

#include<iostream>

#include "../view/gameFrame.cpp"
#include "../ai/AI.cpp"
#include "Plateau.cpp"

using namespace std;

class Game {
  private:
    int phase; //Phase of the game (actually 1 for menus, 2 for pawn placement, 3 for pawn movements, 4 for victory screen ?)
    int turn; //Indicates which player is playing
    int first_pawn;
    void GameLoop();
    GameFrame* gameFrame;
    Plateau* plateau;
    void loop();

  public:
    Game();
    ~Game(){};

    void start();
    void resetGame();
    void switchTurn();
    bool isPlayerPlaying();
    bool isItAt1From(int x1, int x2, int y1, int y2);
};

#endif
