#ifndef AI_H
#define AI_H

#include<iostream>
#include<vector>
#include<math.h>

#include "../tools/Graph.cpp"


using namespace std;

class AI {
  public:
    static vector<int> getDecision(int phase, int turn, int difficulty, vector<vector<int>> gameMatrix);
};

#endif
