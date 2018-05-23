
#include "TextureManager.hpp"

TextureManager::TextureManager() {
  //Loading all the textures
  addTexture("ressources/gameSprites/background.png", "background");
  addTexture("ressources/gameSprites/white.png", "white");
  addTexture("ressources/gameSprites/black.png", "black");
  addTexture("ressources/gameSprites/play.png", "play");
  addTexture("ressources/gameSprites/reset.png","reset");
  addTexture("ressources/gameSprites/quit.png","quit");

  int i,j;
  for (i=1; i<=2; i++) {
    for (j=1; j<=4; j++) {
      addTexture("ressources/gameSprites/player" + std::to_string(i) + "_"+ std::to_string(j) + ".png","player" + std::to_string(i) + "_" + std::to_string(j));
    }
  }

  //Loading all the buttons
  //-------------------------- x  , y   width, height    name
  addButton(std::vector<int> {1600, 1050, 600, 200}, "play");
  addButton(std::vector<int> {1600, 0, 300, 175}, "reset");
  addButton(std::vector<int> {1900, 0, 300, 175}, "quit");
  addButton(std::vector<int> {1600, 600, 600, 200}, "player1_1");
  addButton(std::vector<int> {1600, 600, 600, 200}, "player1_2");
  addButton(std::vector<int> {1600, 600, 600, 200}, "player1_3");
  addButton(std::vector<int> {1600, 600, 600, 200}, "player1_4");
  addButton(std::vector<int> {1600, 800, 600, 200}, "player2_1");
  addButton(std::vector<int> {1600, 800, 600, 200}, "player2_2");
  addButton(std::vector<int> {1600, 800, 600, 200}, "player2_3");
  addButton(std::vector<int> {1600, 800, 600, 200}, "player2_4");
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


void TextureManager::addButton(std::vector<int> coordinates,string name) {
  //cout << name << ": " << coordinates[0] << ":" << coordinates[1] << " | " << coordinates[2] << ":" << coordinates[3] << endl;
  this->buttons.insert({name, coordinates});
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

bool TextureManager::isClicked(string s,int X,int Y) {
    if(X>=getXCoordinates(s) && Y>=getYCoordinates(s) && X<=getXLimit(s) && Y<=getYLimit(s)) {
      return true;
    }
  return false;
}
