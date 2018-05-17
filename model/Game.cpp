
#include "Game.hpp"

Game::Game() {
  this->turn = 1;
  this->phase = 2;
  this->plateau = new Plateau(5);
  this->gameFrame = new GameFrame();
  this->gameState = {0};
}

void Game::start() {
  loop();
}

void Game::loop() {
  int x1=-1,y1;

  while(gameFrame->isOpen())
  {
    if(phase == 1) { //Phase Menu
      int gameChangement = gameFrame->phase1(plateau->getGameMatrix());
      switch(gameChangement){
        case 0: gameState[0] = (gameState[0]+1)%2; //Player1 changes
          break;
        case 1: gameState[1] = (gameState[1]+1)%2; //Player2 changes
          break;
        case 2: gameState[2] = (gameState[2]+1)%2; //Start changes
          break;
      }

      if(gameState[2] == 1)
        phase = 2;

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
        if(plateau->hasSomeoneWon()) {
          phase = 4;
        } else if(plateau->nbPawns() == 8) { //All the pawns are placed
          phase = 3;
        }
      }
    } else if(phase == 3) {
      vector<int> coords;
      coords = gameFrame->phase3(plateau->getGameMatrix(), turn, 0); // isPressed is set to 0 while the pressed informormations are not received, then pass to 1 to catch the release informations

      if(coords.size() >= 2) { //If there has been a click on the "plateau"
         x1 = coords[0];
         y1 = coords[1];
         int x2,y2;

         if (x1>=0){
          do {
            coords = gameFrame->phase3(plateau->getGameMatrix(), turn, 1);
          } while ( coords.size() < 2 );

          if(coords.size() >= 2) {
             x2 = coords[0];
             y2 = coords[1];
             //cout << "Points: " << x1 << ":" << y1 << "    " << x2 << ":" << y2 << endl;
             if (isItAt1From(x1,x2,y1,y2) && (plateau->getValue(x1,y1) == turn) && (plateau->isFreeAt(x2,y2))){ /* Start the drag function if the click is on a player pawn and if the second cell if empty*/
                plateau->moveFromTo(x1, y1, x2, y2);
                switchTurn();
                if(plateau->hasSomeoneWon()) {
                  phase = 4;
                }
             }
           }
         }
       }
    } else if(phase == 4) {
      //Someone has won, print the win screen
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

bool Game::isItAt1From(int x1, int x2, int y1, int y2) {
  int offsetX = abs(x1-x2);
  int offsetY = abs(y1-y2);

  return ((offsetX == 1 && offsetY == 1) || (offsetX == 0 && offsetY == 1) || (offsetX == 1 && offsetY == 0));
}
