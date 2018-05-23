
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
  draw(matrix);
  printTextInTextZone("\nChoose your settings!");
  window.display();

  int gameChangement = -1;
  sf::Event event;

  while (window.pollEvent(event))
  {
      if (event.type == sf::Event::Closed ) {
        window.close();
      } else if(event.type == sf::Event::MouseButtonPressed) {
        int x = event.mouseButton.x;
        int y = event.mouseButton.y;

        if(textureManager->isClicked("quit",x/widthFactor,y/heightFactor)) {
          window.close();
        }

        if(textureManager->isClicked("player1_" + std::to_string(player1State),x/clickWidthFactor,y/clickHeightFactor)){
          gameChangement = 0;
          player1State = updatePlayerState(player1State);
        }

        if(textureManager->isClicked("player2_" + std::to_string(player2State),x/clickWidthFactor,y/clickHeightFactor)){
          gameChangement = 1;
          player2State = updatePlayerState(player2State);
        }

        if(textureManager->isClicked("play",x/clickWidthFactor,y/clickHeightFactor)){
          gameChangement = 2;
        }

        if(textureManager->isClicked("reset",x/clickWidthFactor,y/clickHeightFactor)){
          player1State = 1;
          player2State = 2;
          gameChangement = 3;
        }
      }
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
        int x = event.mouseButton.x;
        int y = event.mouseButton.y;

        if(textureManager->isClicked("quit",x,y)) {
          window.close();
        }

        if(textureManager->isClicked("reset",x,y)) {
          player1State = 1;
          player2State = 2;
          printf("reset\n");
          coords.clear();
          coords.push_back(-1);
          return coords;
        }

        x = x/clickWidthFactor;
        y = y/clickHeightFactor;

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
  if(turn == 1) {
    printTextInTextZone("\nPlayer1 is thinking!");
  } else if(turn == 2) {
    printTextInTextZone("\nPlayer2 is thinking!");
  }
  window.display();

  return coords;
}


vector<int> GameFrame::phase3(vector<vector<int>> matrix, int turn, int isPressed, int x1, int y1) {
  sf::Event event;
  vector<int> coords;
  bool movement = false;

  if(isPressed == 1 && turn == matrix[x1][y1]) {
    matrix[x1][y1] = 0;
    movement = true;
  }

  while (window.pollEvent(event))
  {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
      if(event.type == sf::Event::MouseButtonPressed) {
        int x = event.mouseButton.x;
        int y = event.mouseButton.y;

        if(textureManager->isClicked("quit",x,y)) {
          window.close();
        }

        if(textureManager->isClicked("reset",x,y)) {
          player1State = 1;
          player2State = 2;
          printf("reset\n");
          coords.clear();
          coords.push_back(-1);
          return coords;
        }
      }

      if( event.type == sf::Event::MouseButtonPressed && isPressed==0) { // isPressed is set to 0 while theclick informations hasn't been taken, then pass to 1
        int x = event.mouseButton.x/clickWidthFactor;
        int y = event.mouseButton.y/clickHeightFactor;
        //cout << "drag;";
        if(x>=200 && y>=200) {
          x=(x-200)/200;
          y=(y-175)/200;

          if((unsigned)x<matrix.size() && (unsigned)y<matrix.size()) {
            coords.push_back(x);
            coords.push_back(y);
          }
        }
      }

      if ((event.type == sf::Event::MouseButtonReleased && isPressed==1 )){ // Collect the Release informations only if isPressed==1 to avoid errors
        int x2 = event.mouseButton.x/clickWidthFactor;
        int y2 = event.mouseButton.y/clickHeightFactor;
        //cout << "drop" << endl;
        if(x2>=200 && y2>=200) {
          x2=(x2-200)/200;
          y2=(y2-175)/200;

          if((unsigned)x2<matrix.size() && (unsigned)y2<matrix.size()) {
           coords.push_back(x2);
           coords.push_back(y2);
          }
        }
      }
  }
  draw(matrix);

  if(isPressed == 1 && movement) {
    sf::Sprite pawn;
    sf::Texture pawnTexture;
    if(turn == 1) {
       pawnTexture = textureManager->getTextureByName("white");
    } else if(turn == 2) {
      pawnTexture = textureManager->getTextureByName("black");
    }
    pawn.setTexture(pawnTexture);
    pawn.setScale(widthFactor, heightFactor);

    pawn.setPosition(sf::Mouse::getPosition(window).x-75*widthFactor, sf::Mouse::getPosition(window).y-75*heightFactor);
    window.draw(pawn);
  }

  if(turn == 1) {
    printTextInTextZone("\nPlayer1 is thinking!");
  } else if(turn == 2) {
    printTextInTextZone("\nPlayer2 is thinking!");
  }

  window.display();
  return coords;
}

int GameFrame::phase4(vector<vector<int>> matrix, string message){
  sf::Event event;
  int toDo = -1;
  while (window.pollEvent(event))
  {
    if (event.type == sf::Event::Closed) {
      window.close();
    }
    else if(event.type == sf::Event::MouseButtonPressed) {
      int x = event.mouseButton.x;
      int y = event.mouseButton.y;

      if(textureManager->isClicked("quit",x,y)) {
        window.close();
      }

      if(textureManager->isClicked("reset",x,y)){
        player1State = 1;
        player2State = 2;
        toDo = 0; //to say to the game that he has to reset
      }
    }
    draw(matrix);
    printTextInTextZone(message);
    window.display();
  }
  return toDo;
}


void GameFrame::draw(vector<vector<int>> matrix) {
  //Activation of the factors
  this->clickWidthFactor = (float)window.getSize().x/2400;
  this->clickHeightFactor = (float)window.getSize().y/1350;

  window.clear(sf::Color(173,218,129));

  sf::Sprite background;
  sf::Texture backgroundTexture = textureManager->getTextureByName("background");
  background.setTexture(backgroundTexture);
  background.scale(widthFactor, heightFactor);
  window.draw(background);

  /* All what will be printed is to put here, after the clear and the display */

  /* Menu part */

  drawButton("play");
  drawButton("reset");
  drawButton("quit");
  drawButton("player1_" + std::to_string(player1State));
  drawButton("player2_" + std::to_string(player2State));


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
}

void GameFrame::drawButton(string name) {
  sf::Sprite sprite;
  sf::Texture texture = textureManager->getTextureByName(name);
  sprite.setTexture(texture);
  sprite.setScale(widthFactor, heightFactor);
  sprite.setPosition(textureManager->getXCoordinates(name)*widthFactor,textureManager->getYCoordinates(name)*heightFactor);
  window.draw(sprite);
}


void GameFrame::printTextInTextZone(string textToPrint) {
  int baseX = 1600;
  int baseY = 280;

  sf::Text text;
  sf::Font font;
  font.loadFromFile("ressources/fonts/Lucida.ttf");
  text.setFont(font);
  text.setString(textToPrint);
  text.setCharacterSize(24); // in pixels, not points!
  text.setFillColor(sf::Color::Black);
  //text.setStyle(sf::Text::Bold);
  text.setPosition(baseX*widthFactor, baseY*heightFactor);
  window.draw(text);
}

int GameFrame::updatePlayerState(int state) {
  state = state%4+1;
  return state;
}
