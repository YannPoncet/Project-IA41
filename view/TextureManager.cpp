
#include "TextureManager.hpp"

TextureManager::TextureManager() {
  //Loading all the textures
  addTexture("ressources/gameSprites/background.png", "background");
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
