#include "AI.hpp"

vector<int> AI::getDecision(int phase, int turn, int difficulty, vector<vector<int>> gameMatrix) {
  vector<int> v;

  cout << "je suis l'aiiiiiiiiii, je fais n'importe quoi maid je fais quelque chose putain" << endl;

  if(phase == 2) { //returns a vector of length 2 to know where to put the pawn
    /* TO REPLACE BELOW */
    int x;
    int y;
    do {
      x=floor(rand()%gameMatrix.size());
      y=floor(rand()%gameMatrix.size());
    } while(gameMatrix[x][y] != 0);

    v.push_back(x);
    v.push_back(y);
    /* END OF TO REPLACE BELOW */

  } else if(phase == 3) {
    /* TO REPLACE BELOW */
    int x1;
    int y1;
    do {
      x1=floor(rand()%gameMatrix.size());
      y1=floor(rand()%gameMatrix.size());
    } while(gameMatrix[x1][y1] != turn);

    v.push_back(x1);
    v.push_back(y1);
    //bon du coup là en dessous ça fera une tp mais bon c'est juste pour tester
    int x2;
    int y2;
    do {
      x2=floor(rand()%gameMatrix.size());
      y2=floor(rand()%gameMatrix.size());
    } while(gameMatrix[x2][y2] != 0);

    v.push_back(x2);
    v.push_back(y2);
    /* END OF TO REPLACE */
  }

  return v;
}
