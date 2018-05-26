#ifndef MINMAX_H
#define MINMAX_H

#include<iostream>
#include<vector>
#include<math.h>

#include "../model/Plateau.hpp"


using namespace std;

class MinMax {
  public:
    //launches a MinMax algorithm while we are in phase 2
    static vector<int> phase2(Plateau* plateau, int player, int turn);

    static int miniMax(vector<vector<int>> moves, Plateau* plateau, int player, int turn);

    //tells if the player that currently plays (known with turn) has won or not
    static int winning(Plateau* plateau, int turn);
};

#endif
