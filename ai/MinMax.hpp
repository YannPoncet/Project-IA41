#ifndef MINMAX_H
#define MINMAX_H

#include<iostream>
#include<vector>
#include<math.h>
#include <limits>

#include "../model/Plateau.hpp"


using namespace std;

class MinMax {
  public:
    //launches a MinMax algorithm while we are in phase 2
    static vector<int> phase2(Plateau* plateau, int player, int turn);

    //launches the minMax algorithm and returns the move to do
    vector<int> minMax(Plateau* plateau, int profondeur, int player, int turn);

    //the max part of the algorithm
    int tourMax(Plateau* plateau, int p, vector<int> alphaBeta, vector<int> move, int player, int turn);
    //the min part of the algorithm
    int tourMin(Plateau* plateau, int p, vector<int> alphaBeta, vector<int> move, int player, int turn);
    //used to tell how much points we give to a plateau :D
    int eval(vector<vector<int>> matrix, int player);

};

#endif
