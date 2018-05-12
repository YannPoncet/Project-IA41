#ifndef GAME_H
#define GAME_H

#include<iostream>

#include "../view/gameFrame.cpp"
#include "Plateau.cpp"

using namespace std;

class Game {
  private:
    void GameLoop();
    GameFrame* gameFrame;
    Plateau* plateau;
    void loop();

  public:
    Game();
    ~Game(){};

    void start();

};

#endif
