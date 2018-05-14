
#include "Game.hpp"

Game::Game() {
  this->turn = 1;
  this->phase = 2;
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
    if(phase == 1) {

    } else if(phase == 2) {
      vector<int> coords;
      coords = gameFrame->phase2(plateau->getGameMatrix(), turn);
      if(coords.size() >= 2) { //If there has been a click on the "plateau"
        cout << "Clicked at: " << coords[0] << ":" << coords[1] << endl;
        int x = coords[0];
        int y = coords[1];
        if(plateau->isFreeAt(x,y)) {
          plateau->addNewPawn(x,y,turn);
        }
        switchTurn();
        if(plateau->nbPawns() == 8) { //All the pawns are placed
          phase = 3;
        }
      }
    } else if(phase == 3) {
      vector<int> coords;
      coords = gameFrame->phase2(plateau->getGameMatrix(), turn);
      if(coords.size() >= 2) { //If there has been a click on the "plateau"
        //TODO
      }
    }

  }
}

void Game::switchTurn() {
  if(turn == 2) {
    turn = 1;
  } else if(turn  == 1) {
    turn = 2;
  }
}
