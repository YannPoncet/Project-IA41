
#include "TextureManager.hpp"

TextureManager::TextureManager() {
  //Loading all the textures
  addTexture("ressources/gameSprites/background.png", "background");
  addTexture("ressources/gameSprites/white.png", "white");
  addTexture("ressources/gameSprites/black.png", "black");
  addTexture("ressources/gameSprites/play.png", "play");
  addTexture("ressources/gameSprites/reset.png","reset");
  addTexture("ressources/gameSprites/quit.png","quit");
  addTexture("ressources/gameSprites/player1_1.png","player1_1");
  addTexture("ressources/gameSprites/player1_2.png","player1_2");
  addTexture("ressources/gameSprites/player2_1.png","player2_1");
  addTexture("ressources/gameSprites/player2_2.png","player2_2");


  addButton(std::vector<int> {(int)(width-800*widthFactor),(int)(height-375*heightFactor),(int)(600*widthFactor),(int)(200*heightFactor)},"play");
  addButton(std::vector<int> {(int)(width-800*widthFactor),0,300,175},"reset");
  addButton(std::vector<int> {(int)(width-500*widthFactor),0,300,175},"quit");
  addButton(std::vector<int> {(int)(width-800*widthFactor),(int)(300*heightFactor),600,200},"player1");
  addButton(std::vector<int> {(int)(width-800*widthFactor),(int)(500*heightFactor),600,200},"player2");
}

bool TextureManager::addTexture(string path, string name) {
  sf::Texture texture;
  bool b = texture.loadFromFile(path);
  this->textures.insert({name, texture});
  return b;
}

sf::Texture TextureManager::getTextureByName(string s) {
  return this->textures[s];
}


void TextureManager::addButton(std::vector<int> v,string name) {
  this->buttons.insert({name, v});
}

int TextureManager::getXCoordinates(string s) {
  return this->buttons[s].at(0);
}

int TextureManager::getYCoordinates(string s) {
  return this->buttons[s].at(1);
}

int TextureManager::getXLimit(string s) {
  return this->buttons[s].at(0) + this->buttons[s].at(2);
}

int TextureManager::getYLimit(string s) {
  return this->buttons[s].at(1) + this->buttons[s].at(3);
}
