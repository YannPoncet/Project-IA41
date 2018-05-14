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

  public:
    TextureManager();
    ~TextureManager(){};

    sf::Texture getTextureByName(string s);
    bool addTexture(string path, string name);
};

#endif
