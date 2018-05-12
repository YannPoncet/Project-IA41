
#include<iostream>
#include "model/Game.cpp"

int main(int argc, char const *argv[]) {
  Game* game = new Game();
  game->start();
  return 0;
}
