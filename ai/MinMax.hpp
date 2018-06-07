#ifndef MINMAX_H
#define MINMAX_H

#include<iostream>
#include<vector>
#include<math.h>
#include<unordered_map>
#include <limits>

#include "../model/Plateau.hpp"


using namespace std;

class MinMax {
  public:
    //launches a MinMax algorithm while we are in phase 2
    //static vector<int> phase2(Plateau* plateau, int player, int turn);

    //launches the minMax algorithm and returns the move to do
    vector<int> minMax(Plateau* plateau, int profondeur, int player, int turn);

  private:
    //the max part of the algorithm
    int turnMax(Plateau* plateau, int p, int &alpha, int &beta, int &x, int &y, int player, int turn);
    //the min part of the algorithm
    int turnMin(Plateau* plateau, int p, int &alpha, int &beta, int &x, int &y, int player, int turn);

    //returns the evalutation of a state of the game
    int eval(vector<vector<int>> gameMatrix, int player);
    //used in eval to locate a pattern
    int findPattern(vector<vector<int>> gameMatrix, int x, int y, int player);
    //test the associoted pattern at the x y coordinates
    bool testAPattern(vector<vector<int>> gameMatrix, int patternRank, int pattern[][2], int x, int y, int player);
};

#endif
