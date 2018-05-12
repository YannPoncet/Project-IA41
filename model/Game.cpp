
#include "Game.hpp"

Game::Game() {
  this->plateau = new Plateau(5);
}

void Game::start() {
  mainWindow.create(sf::VideoMode(1024,768,32),"Teeko du futur");
  loop();
}

void Game::loop() {
  while (mainWindow.isOpen())
  {
    sf::Event event;
    while (mainWindow.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            mainWindow.close();
    }
    mainWindow.clear(sf::Color(173,218,129));
    mainWindow.display();
  }
}
