#ifndef GAMEFRAME_H
#define GAMEFRAME_H

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

#include "TextureManager.cpp"

using namespace std;

class GameFrame {
  private:
    int width = 1200;
    int height = 675;
    float widthFactor = (float)width/2400;
    float heightFactor = (float)height/1350;
    sf::RenderWindow window;

    TextureManager* textureManager;
    //vector<sf::Texture> textures; TODO
    sf::Texture bgTexture;
    void GameLoop();


  public:
    GameFrame();
    ~GameFrame();

    void draw(vector<vector<int>> matrix);
    bool isOpen();
};

#endif
