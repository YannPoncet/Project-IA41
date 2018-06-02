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
    static vector<int> minMax(Plateau* plateau, int profondeur, int player, int turn);

    //the max part of the algorithm
    static int tourMax(Plateau* plateau, int p, vector<int> alphaBeta, vector<int> move, int player, int turn);
    //the min part of the algorithm
    static int tourMin(Plateau* plateau, int p, vector<int> alphaBeta, vector<int> move, int player, int turn);

    //returns the evalutation of a state of the game
    static int eval(vector<vector<int>> gameMatrix, int player);
    //used in eval to locate a pattern
    static vector<int> findPattern(vector<vector<int>> gameMatrix, int x, int y, int player);
};

#endif
