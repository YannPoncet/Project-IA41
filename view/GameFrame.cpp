
#include "GameFrame.hpp"

GameFrame::GameFrame() {
  window.create(sf::VideoMode(width,height,32),"Teeko du futur");
  window.clear(sf::Color(173,218,129));
  window.display();

  this->textureManager = new TextureManager;

  if (!bgTexture.loadFromFile("ressources/gameSprites/background.png")) {
    printf("Failed to load the background");
  }
}

GameFrame::~GameFrame(){
  delete this->textureManager;
}

bool GameFrame::isOpen() {
  return window.isOpen();
}

void GameFrame::draw(vector<vector<int>> matrix) {
  sf::Event event;

  while (window.pollEvent(event))
  {
      if (event.type == sf::Event::Closed)
          window.close();
  }

  window.clear(sf::Color(173,218,129));

  sf::Sprite background;
  sf::Texture texture = textureManager->getTextureByName("background");
  background.setTexture(texture);
  background.scale(widthFactor, heightFactor);
  window.draw(background);


  /* All what will be printed is to put here, after the clear and the display */
  sf::Text text;
  sf::Font font;
  font.loadFromFile("ressources/fonts/Julius.ttf");
  text.setFont(font); // font is a sf::Font
  text.setString(L"Tu t'es enfin mis au boulot, c'est pas trop tôt dis donc !\n\nBon, c'est dégeulasse mais ça suffira pour le début:");
  text.setCharacterSize(24); // in pixels, not points!
  text.setFillColor(sf::Color::Black);
  text.setStyle(sf::Text::Bold);
  window.draw(text);


  for(int x=0; (unsigned)x<matrix.size(); x++) {
    for(int y=0; (unsigned)y<matrix.size(); y++) {
      sf::CircleShape shape(20.f);
      if(matrix[x][y]==0) {
        shape.setFillColor(sf::Color::Black);
      } else if(matrix[x][y]==1) {
        shape.setFillColor(sf::Color::Green);
      } else if(matrix[x][y]==2) {
        shape.setFillColor(sf::Color::Blue);
      }
      shape.setPosition(x*60+250, y*60+100);
      window.draw(shape);
    }
  }

  window.display();
}
