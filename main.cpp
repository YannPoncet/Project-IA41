
#include<iostream>
#include "model/Game.cpp"

int main(int argc, char const *argv[]) {
  srand(time(NULL));
  Game* game = new Game();
  game->start();
  return 0;
}
