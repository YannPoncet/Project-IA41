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
    sf::Texture bgTexture;
    void GameLoop();


  public:
    GameFrame();
    ~GameFrame();

    void draw(vector<vector<int>> matrix);
    void printTextInTextZone(string textToPrint);

    /**phase1 is for the menus : if it returns
    * -1 nothing to change
    * 0 Player1 is Human/AI
    * 1 Player2 is Human/AI
    * 2 Start the game
    */
    int phase1(vector<vector<int>> matrix);
    vector<int> phase2(vector<vector<int>> matrix, int turn);
    vector<int> phase3(vector<vector<int>> matrix, int turn, int isPressed, int x1, int y1);
    void phase4(vector<vector<int>> matrix, string message);

    bool isOpen();

    bool isClicked(string,int,int);
};

#endif
