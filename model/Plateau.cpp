
#include "Plateau.hpp"

Plateau::Plateau(int nbCells) {
  this->nbCells = nbCells;

  gameMatrix.resize(nbCells); //Initialize the matrix to nbCells colls
  for(int i=0; i<nbCells; i++) {
    gameMatrix[i].resize(nbCells); //Initialize all the cols
  } //The gameMatrix is now filled with 0s

}

vector<vector<int>> Plateau::getGameMatrix() {
  return this->gameMatrix;
}

void Plateau::reset() {
  for(int i=0; i<this->nbCells; i++) {
    for(int j=0; j<this->nbCells; j++) {
      this->gameMatrix[i][j]=0; //Initialize all the cells
    }
  } //The gameMatrix is now filled with 0s
}

void Plateau::addNewPawn(int x, int y, int value) {
  this->gameMatrix[x][y]=value;
}

void Plateau::moveFromTo(int fromX, int fromY, int toX, int toY) {
  //We're supposing the we can move here
  gameMatrix[toX][toY] = gameMatrix[fromX][fromY];
  gameMatrix[fromX][fromY] = 0;
}

bool Plateau::isFreeAt(int x, int y) {
  return this->gameMatrix[x][y]==0;
}

int Plateau::hasSomeoneWon() {
  int currentVal = 0;
  bool firstTested = false;
  bool secondTested = false;
  for(int x=0; x<this->nbCells; x++) {
    for(int y=0; y<this->nbCells; y++) {
      currentVal = this->gameMatrix[x][y];
      if(currentVal == 1 && !firstTested) { //we find the first pawn of the first player
        firstTested = true;
        int result = 0;
        if((result = this->testPattern(x,y,currentVal))==1)
          return result;
      } else if(currentVal == 2 && !secondTested) { //we find the first pawn of the second player
        secondTested = true;
        int result = 0;
        if((result = this->testPattern(x,y,currentVal))==2)
          return result;
      }
    }
  }
  return 0;
}

int Plateau::testPattern(int x, int y, int currentVal) {
  //Stores the different configurations to win
  int pattern[5][3][2] = {
    {{1,1},{2,2},{3,3}}, //diag1
    {{-1,-1},{-2,-2},{-3,-3}}, //diag2
    {{1,0},{0,1},{1,1}}, //square
    {{1,0},{2,0},{3,0}}, //horizontal
    {{0,1},{0,2},{0,3}} //vertical
  };

  for(int pat=0; pat<5; pat++) {
    bool testBool = true;
    int coord = 0;
    do {
      int testX = x+pattern[pat][coord][0];
      int testY = y+pattern[pat][coord][1];
      if(testX>=0 && testX<this->nbCells && testY>=0 && testY<this->nbCells) { //if we're outside of the gameMatrix
        if(this->gameMatrix[testX][testY] != currentVal) {
          testBool = false;
        }
      } else {
        testBool = false;
      }
      coord++;
    } while(testBool == true && coord <3);

    if(testBool == true) { //if test bool is still at true, we have found a victory configuration
      return currentVal;
    }
  }
  return 0; //we have tested all the patterns, none of them were "victorious", so the currentVal player has not won yet
}

int Plateau::nbPawns() {
  int nb = 0;
  for(int x=0; x<this->nbCells; x++) {
    for(int y=0; y<this->nbCells; y++) {
      if(this->gameMatrix[x][y] != 0) {
        nb++;
      }
    }
  }
  return nb;
}

int Plateau::getValue(int x, int y) {
  return this->gameMatrix[x][y];
}
