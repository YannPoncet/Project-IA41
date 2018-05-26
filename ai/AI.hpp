#ifndef AI_H
#define AI_H

#include<iostream>
#include<vector>
#include<math.h>

#include "../ai/MinMax.hpp"
#include "../model/Plateau.hpp"


using namespace std;

class AI {
  public:
    static vector<int> getDecision(int phase, int turn, int difficulty, Plateau* plateau);
};

#endif
