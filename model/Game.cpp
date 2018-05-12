
#include "Game.hpp"

Game::Game() {
  this->plateau = new Plateau(5);
  this->gameFrame = new GameFrame();
}

void Game::start() {
  loop();
}

void Game::loop() {

  //TO REMOVE
  plateau->addNewPawn(1,2,2);
  plateau->addNewPawn(4,4,1);
  //END of TO REMOVE

  while(gameFrame->isOpen())
  {
    gameFrame->draw(plateau->getGameMatrix());
  }
}
