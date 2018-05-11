#ifndef PLATEAU_H
#define PLATEAU_H

#include<iostream>
#include<vector>

using namespace std;

class Plateau {
  private:
    int nbCells; //number of cells in the game
    vector<vector<int>> gameMatrix; //it'll contain the locations of the different "Pions"

  public:
    Plateau(){};
    Plateau(int nbCells);
    ~Plateau(){};

    void reset();
    void moveFromTo(int fromX, int fromY, int toX, int toY);
    bool isFreeAt(int x, int y);
};

#endif
