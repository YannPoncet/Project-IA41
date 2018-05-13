#ifndef GAMEFRAME_H
#define GAMEFRAME_H

#include<iostream>
#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>
#include<vector>

using namespace std;

class GameFrame {
  private:
    sf::RenderWindow window;
    //vector<sf::Sprite> sprites;
    sf::Sprite background;
    void GameLoop();


  public:
    GameFrame();
    ~GameFrame(){};

    void draw(vector<vector<int>> matrix);
    bool isOpen();
};

#endif
