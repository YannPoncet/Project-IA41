#include "AI.hpp"


vector<int> AI::getDecision(int phase, int turn, int difficulty, Plateau* plateau) {
  vector<int> v;

  cout << "    --> Waiting AI's decision" << endl;

  Plateau* newPlateau = new Plateau(5, plateau->getGameMatrix());
  MinMax* minMax;
  v = minMax->minMax(newPlateau, difficulty+1, turn, turn, phase); //difficulty = depth

  cout << "    <-- AI has decided" << endl;
  return v;
}
