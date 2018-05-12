#ifndef PLATEAU_H
#define PLATEAU_H

#include<iostream>
#include<vector>

using namespace std;

class Plateau {
  private:
    int nbCells; //number of cells in the game
    vector<vector<int>> gameMatrix; //it'll contain the locations of the different "Pions"

    int testPattern(int x, int y, int currentVal);

  public:
    Plateau(){};
    Plateau(int nbCells);
    ~Plateau(){};

    /* Resets the gameMatrix to 0s */
    void reset();

    /* Moves a pawn from one place to another without verifications */
    void moveFromTo(int fromX, int fromY, int toX, int toY);

    /* Returns true if a cell is empty */
    bool isFreeAt(int x, int y);

    /* If someone has won, returns its number, 0 otherwise */
    int hasSomeoneWon();
};

#endif
