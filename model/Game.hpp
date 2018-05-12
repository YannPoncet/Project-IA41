#ifndef GAME_H
#define GAME_H

#include<iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Plateau.cpp"



using namespace std;

class Game {
  private:
    void GameLoop();
    sf::RenderWindow mainWindow;
    Plateau* plateau;
    void loop();

  public:
    Game();
    ~Game(){};

    void start();

};

#endif
