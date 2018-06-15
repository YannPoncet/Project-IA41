
#include "Game.hpp"

Game::Game() {
  this->turn = 1;
  this->phase = 1;
  this->first_pawn=0;
  this->plateau = new Plateau(5);
  this->gameFrame = new GameFrame();
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
        case 2: phase = 2; //Start
          break;
      }

    } else if(phase == 2) {
      vector<int> coords;
      coords = gameFrame->phase2(plateau->getGameMatrix(), turn);

      if(isPlayerPlaying()) {
        if(coords.size()==1){
          resetGame();
        }
        else if(coords.size() >= 2) { //If there has been a click on the "plateau"
          int x = coords[0];
          int y = coords[1];
          if(plateau->isFreeAt(x,y)) {
            plateau->addNewPawn(x,y,turn);
            switchTurn();
          }
          if(plateau->hasSomeoneWon()) {
            phase = 4;
          } else if(plateau->nbPawns() == 8) { //All the pawns are placed
            phase = 3;
          }
        }
      } else { //the IA shall play
        vector<int> decision;

        // Random for the first pawn
        int x,y;
        if(first_pawn==0){   //Set to 0 only for the first move of the AI to generate the first random point
            do{
             x=rand()%5;
             y=rand()%5;
           }while(plateau->getValue(x,y)!=0);
           decision.push_back(x);
           decision.push_back(y);
           first_pawn=1;
        }
        else decision = AI::getDecision(phase, turn, gameFrame->getCurrentPlayerState(turn), plateau);


        //we add the pawn where the AI decided
        plateau->addNewPawn(decision[0],decision[1],turn);
        switchTurn();
        if(plateau->hasSomeoneWon()) {
          phase = 4;
        } else if(plateau->nbPawns() == 8) { //All the pawns are placed
          phase = 3;
        }
      }

    } else if(phase == 3) {
      vector<int> coords;
      coords = gameFrame->phase3(plateau->getGameMatrix(), turn, 0, 0, 0); // isPressed is set to 0 while the pressed informormations are not received, then pass to 1 to catch the release informations

      if(isPlayerPlaying()) {
        if(coords.size()==1){ //reset
          resetGame();
        }
        else if(coords.size() >= 2) { //If there has been a click on the "plateau"
           x1 = coords[0];
           y1 = coords[1];
           int x2,y2;

           if (x1>=0){
            do {
              coords = gameFrame->phase3(plateau->getGameMatrix(), turn, 1, x1, y1);
            } while ( coords.size() < 2 );

            if(coords.size() >= 2) {
               x2 = coords[0];
               y2 = coords[1];
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
       } else { //the IA shall play
         vector<int> decision;

         decision = AI::getDecision(phase, turn, gameFrame->getCurrentPlayerState(turn), plateau);


         //we add the pawn where the AI decided
         plateau->moveFromTo(decision[0], decision[1], decision[2], decision[3]);
         switchTurn();
         if(plateau->hasSomeoneWon()) {
           phase = 4;
         }
       }
    } else if(phase == 4) {
      //We wait untill we reset the gameFrame

      string winMessage;
      if(turn == 2) { //because we already have done the switchTurn
        winMessage = "Player1 has won!\nClick on reset to \nrestart";
      } else if(turn == 1) {
        winMessage = "Player2 has won!\nClick on reset to \nrestart";
      }

      if(gameFrame->phase4(plateau->getGameMatrix(), winMessage)==0){ //0:reset
        resetGame();
      }

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

void Game::resetGame() {
  plateau->reset();
  phase = 1;
  turn = 1;
  first_pawn=0;
}

bool Game::isPlayerPlaying() {
  if (turn == 1) {
    if ( gameFrame->getPlayer1State() == 1) {
      return true;
    }
    else
    return false;
  }

  else if ( gameFrame->getPlayer2State() == 1) {
    return true;
  }
  else
  return false;
}
