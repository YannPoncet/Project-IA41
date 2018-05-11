
#include "Plateau.hpp"

Plateau::Plateau(int nbCells) {
  this->nbCells = nbCells;

  gameMatrix.resize(nbCells); //Initialize the matrix to nbCells colls
  for(int i=0; i<nbCells; i++) {
    gameMatrix[i].resize(nbCells); //Initialize all the cols
  } //The gameMatrix is now filled with 0s

}

void Plateau::reset() {
  for(int i=0; i<this->nbCells; i++) {
    this->gameMatrix[i].resize(this->nbCells); //Initialize all the cols
  } //The gameMatrix is now filled with 0s
}

void Plateau::moveFromTo(int fromX, int fromY, int toX, int toY) {
  //We're supposing the we can move here
  gameMatrix[toX][toY] = gameMatrix[fromX][fromY];
  gameMatrix[fromX][fromY] = 0;
}


bool Plateau::isFreeAt(int x, int y) {
  return this->gameMatrix[x][y]==0;
}
