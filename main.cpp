
#include<iostream>
#include "model/Game.cpp"

int main(int argc, char const *argv[]) {
  cout << "--> Starting" << endl;
  srand(time(NULL));
  Game* game = new Game();
  game->start();
  return 0;
}
