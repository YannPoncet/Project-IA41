
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

int GameFrame::phase1(vector<vector<int>> matrix){
  sf::Event event;
  int gameChangement = -1;

  if("Button Player1 is pressed"){
    gameChangement = 0;
  }

  if("Button Player2 is pressed"){
    gameChangement = 1;
  }

  if("Button Start is pressed"){
    gameChangement = 2;
  }

  return gameChangement;
}

vector<int> GameFrame::phase2(vector<vector<int>> matrix, int turn) {
  sf::Event event;
  vector<int> coords;

  while (window.pollEvent(event))
  {
      if (event.type == sf::Event::Closed) {
        window.close();
      } else if(event.type == sf::Event::MouseButtonPressed) {
        int x = event.mouseButton.x/widthFactor;
        int y = event.mouseButton.y/heightFactor;

        if(x>=200 && y>=200) {
          x=(x-200)/200;
          y=(y-175)/200;

          if((unsigned)x<matrix.size() && (unsigned)y<matrix.size()) {
            coords.push_back(x);
            coords.push_back(y);
          }
        }
      }
  }

  draw(matrix);

  return coords;
}

  vector<int> GameFrame::phase3(vector<vector<int>> matrix, int turn) {
    sf::Event event;
    vector<int> coords;

    int isPressed =0;

    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed) {
          window.close();
        }

        if( (event.type == sf::Event::MouseButtonPressed) && (isPressed==0) ) { // isPressed is set to 0 while theclick informations hasn't been taken, then pass to 1
          int x = event.mouseButton.x/widthFactor;
          int y = event.mouseButton.y/heightFactor;

          if(x>=200 && y>=200) {
            x=(x-200)/200;
            y=(y-175)/200;

            if((unsigned)x<matrix.size() && (unsigned)y<matrix.size()) {
              coords.push_back(x);
              coords.push_back(y);
              isPressed=1;
            }
          }

        }

        if ((event.type == sf::Event::MouseButtonReleased) && (isPressed==1) ){ // Collect the Release informations only if isPressed==1 to avoid errors
          int x = event.mouseButton.x/widthFactor;
          int y = event.mouseButton.y/heightFactor;

          if(x>=200 && y>=200) {
            x=(x-200)/200;
            y=(y-175)/200;

            if((unsigned)x<matrix.size() && (unsigned)y<matrix.size()) {
             coords.push_back(x);
             coords.push_back(y);
            }
        }

    }
  }

  draw(matrix);

  return coords;
}

void GameFrame::draw(vector<vector<int>> matrix) {
  window.clear(sf::Color(173,218,129));

  sf::Sprite background;
  sf::Texture backgroundTexture = textureManager->getTextureByName("background");
  background.setTexture(backgroundTexture);
  background.scale(widthFactor, heightFactor);
  window.draw(background);

  /* All what will be printed is to put here, after the clear and the display */
  sf::Text text;
  sf::Font font;
  font.loadFromFile("ressources/fonts/Julius.ttf");
  text.setFont(font); // font is a sf::Font
  text.setString(L"TEEEEEKOOOOOOOOOO WOUHOUUUU AKA le jeu de bite");
  text.setCharacterSize(24); // in pixels, not points!
  text.setFillColor(sf::Color::Black);
  text.setStyle(sf::Text::Bold);
  window.draw(text);

  /* Menu part */


  for(int x=0; (unsigned)x<matrix.size(); x++) {
    for(int y=0; (unsigned)y<matrix.size(); y++) {
      if(matrix[x][y]==1 || matrix[x][y]==2) {
        sf::Sprite pawn;
        sf::Texture pawnTexture;
        if(matrix[x][y]==1) {
          pawnTexture = textureManager->getTextureByName("white");
        } else if(matrix[x][y]==2) {
          pawnTexture = textureManager->getTextureByName("black");
        }
        pawn.setTexture(pawnTexture);
        pawn.scale(widthFactor, heightFactor);
        pawn.setPosition(25*widthFactor+200*widthFactor*(1+x),25*heightFactor+heightFactor*(175+200*y));
        window.draw(pawn);
      }
    }
  }

  window.display();
}
