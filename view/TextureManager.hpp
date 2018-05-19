#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include<iostream>
#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>
#include<vector>
#include<unordered_map>

using namespace std;

class TextureManager {
  private:
    std::unordered_map<std::string, sf::Texture> textures;
    std::unordered_map<std::string, std::vector<int>> buttons;

  public:
    TextureManager();
    ~TextureManager(){};

    sf::Texture getTextureByName(string s);
    bool addTexture(string path, string name);

    int getXCoordinates(string s);
    int getYCoordinates(string s);
    int getXLimit(string s);
    int getYLimit(string s);
    void addButton(std::vector<int> v, string name);
    bool isClicked(string s,int,int);
};

#endif
