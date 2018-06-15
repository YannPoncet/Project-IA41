#include "AI.hpp"


vector<int> AI::getDecision(int phase, int turn, int difficulty, Plateau* plateau) {
  vector<int> v;

  cout << "je suis l'aiiiiiiiiii, je fais n'importe quoi maid je fais quelque chose putain" << endl;

  Plateau* newPlateau = new Plateau(5, plateau->getGameMatrix());
  MinMax* minMax;
  v = minMax->minMax(newPlateau, difficulty+1, turn, turn, phase); //difficulty = depth

  return v;
}
