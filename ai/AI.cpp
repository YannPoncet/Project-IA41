#include "AI.hpp"


vector<int> AI::getDecision(int phase, int turn, int difficulty, Plateau* plateau) {
  vector<int> v;

  cout << "je suis l'aiiiiiiiiii, je fais n'importe quoi maid je fais quelque chose putain" << endl;

  if(phase == 2) { //returns a vector of length 2 to know where to put the pawn

    /*Plateau* newPlateau = new Plateau(5, plateau->getGameMatrix());
    v = MinMax::phase2(newPlateau, turn, turn);
    */

    /* TO REPLACE BELOW */
    int x;
    int y;
    do {
      x=floor(rand()%plateau->getGameMatrix().size());
      y=floor(rand()%plateau->getGameMatrix().size());
    } while(plateau->getGameMatrix()[x][y] != 0);

    v.push_back(x);
    v.push_back(y);
    /* END OF TO REPLACE BELOW */

  } else if(phase == 3) {
    /* TO REPLACE BELOW */
    int x1;
    int y1;
    do {
      x1=floor(rand()%plateau->getGameMatrix().size());
      y1=floor(rand()%plateau->getGameMatrix().size());
    } while(plateau->getGameMatrix()[x1][y1] != turn);

    v.push_back(x1);
    v.push_back(y1);
    //bon du coup là en dessous ça fera une tp mais bon c'est juste pour tester
    int x2;
    int y2;
    do {
      x2=floor(rand()%plateau->getGameMatrix().size());
      y2=floor(rand()%plateau->getGameMatrix().size());
    } while(plateau->getGameMatrix()[x2][y2] != 0);

    v.push_back(x2);
    v.push_back(y2);
    /* END OF TO REPLACE */
  }

  return v;
}
