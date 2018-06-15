#include "MinMax.hpp"

vector<int> MinMax::minMax(Plateau* plateau, int profondeur, int player, int turn, int phase){

  vector<int> move;
  int alpha = std::numeric_limits<int>::min();
  int beta = std::numeric_limits<int>::max();

  switch(phase){
    case 2:{
      int x = -1;
      int y = -1;

      turnMaxPhase2(plateau, profondeur, alpha, beta, x, y, player, turn);

      move.push_back(x); //x
      move.push_back(y); //y
    }
        break;

    case 3:{
      int startX = -1;
      int startY = -1;
      int endX = -1;
      int endY = -1;

      turnMaxPhase3(plateau, profondeur, alpha, beta, startX, startY, endX, endY, player, turn);

      move.push_back(startX);
      move.push_back(startY);
      move.push_back(endX);
      move.push_back(endY);
    }
        break;
  }

  return move;
}

int MinMax::turnMaxPhase2(Plateau* plateau, int p, int alpha, int beta, int &x, int &y, int player, int turn){

  if(plateau->hasSomeoneWon() || p==0){
    int tmp=eval(plateau->getGameMatrix(), player);
    return tmp;
  }

  if(plateau->nbPawns()==8){
    int endX;
    int endY;
    return turnMaxPhase3(plateau, p-1, alpha, beta, x, y, endX, endY, player, turn);
  }

  int u = std::numeric_limits<int>::min();
  int actionX = -1;
  int actionY = -1;

  for(int i=0; i<5; i++){
    for(int j=0; j<5 ;j++){
      if(plateau->getGameMatrix()[i][j]==0){ //case vide
        plateau->addNewPawn(i,j,turn);

        int tmp = turnMinPhase2(plateau, p-1, alpha, beta, x, y, player, (turn%2)+1);
        if(tmp>u){ //max
          actionX = i;
          actionY = j;
          u = tmp;
        }
        plateau->addNewPawn(i,j,0);

        if(u>=beta){ //cut branches
          x = actionX;
          y = actionY;
          return u;
        }

        if(alpha<u)
          alpha=u;
      }
    }
  }

  x = actionX;
  y = actionY;
  return u;
}

int MinMax::turnMinPhase2(Plateau* plateau, int p, int alpha, int beta, int &x, int &y, int player, int turn){

  if(plateau->hasSomeoneWon() || p==0){
    int tmp=eval(plateau->getGameMatrix(), player);
    return tmp;
  }

  if(plateau->nbPawns()==8){
    int endX;
    int endY;
    return turnMinPhase3(plateau, p-1, alpha, beta, x, y, endX, endY, player, turn);
  }

  int u = std::numeric_limits<int>::max();
  int actionX = -1;
  int actionY = -1;

  for(int i=0; i<5; i++){
    for(int j=0; j<5 ;j++){
      if(plateau->getGameMatrix()[i][j]==0){ //case vide
        plateau->addNewPawn(i,j,turn);
        int tmp = turnMaxPhase2(plateau, p-1, alpha, beta, x, y, player, (turn%2)+1);
        if(tmp<u){ //min
          actionX = i;
          actionY = j;
          u = tmp;
        }
        plateau->addNewPawn(i,j,0);

        if(u<=alpha){ //cut branches
          x = actionX;
          y = actionY;
          return u;
        }

        if(beta>u)
          beta=u;
      }
    }
  }

  x = actionX;
  y = actionY;
  return u;
}

int MinMax::turnMaxPhase3(Plateau* plateau, int p, int alpha, int beta, int &startX, int &startY, int &endX, int &endY, int player, int turn){

  if(plateau->hasSomeoneWon() || p==0){
    int tmp=eval(plateau->getGameMatrix(), player);
    return tmp;
  }

  int u = std::numeric_limits<int>::min();
  int startActionX = -1;
  int startActionY = -1;
  int endActionX = -1;
  int endActionY = -1;

  for(int i=0; i<5; i++){
    for(int j=0; j<5 ;j++){
      if(plateau->getGameMatrix()[i][j]==turn){ //the current player's pawn
        plateau->addNewPawn(i,j,0); //deleting the pawn on this position

        for(int k=i-1; k<i+2; k++){ //checking the positions around the founded pawn
          for(int l=j-1; l<j+2; l++){
            if(k>=0 && k<5 && l>=0 && l<5 && (k!=i || l!=j) && (plateau->getGameMatrix()[k][l]==0)){ //on the board && empty
              plateau->addNewPawn(k,l,turn); //adding the pawn on this position
              int tmp = turnMinPhase3(plateau, p-1, alpha, beta, startX, startY, endX, endY, player, (turn%2)+1);
              if(tmp>u){ //max
                startActionX = i;
                startActionY = j;
                endActionX = k;
                endActionY = l;
                u = tmp;
              }

              if(u>=beta){ //cut branches
                startX = startActionX;
                startY = startActionY;
                endX = endActionX;
                endY = endActionY;
                plateau->addNewPawn(k,l,0);
                plateau->addNewPawn(i,j,turn);
                return u;
              }

              if(alpha<u)
                alpha=u;

              plateau->addNewPawn(k,l,0); // deleting the pawn for the next steps
            }
          }
        }
        plateau->addNewPawn(i,j,turn); // replacing the pawn for the next steps
      }
    }
  }

  startX = startActionX;
  startY = startActionY;
  endX = endActionX;
  endY = endActionY;
  return u;
}

int MinMax::turnMinPhase3(Plateau* plateau, int p, int alpha, int beta, int &startX, int &startY, int &endX, int &endY, int player, int turn){

  if(plateau->hasSomeoneWon() || p==0){
    int tmp=eval(plateau->getGameMatrix(), player);
    return tmp;
  }

  int u = std::numeric_limits<int>::max();
  int startActionX = -1;
  int startActionY = -1;
  int endActionX = -1;
  int endActionY = -1;

  for(int i=0; i<5; i++){
    for(int j=0; j<5 ;j++){
      if(plateau->getGameMatrix()[i][j]==turn){ //the current player's pawn
        plateau->addNewPawn(i,j,0); //deleting the pawn on this position

        for(int k=i-1; k<i+2; k++){ //checking the positions around the founded pawn
          for(int l=j-1; l<j+2; l++){
            if(k>=0 && k<5 && l>=0 && l<5 && (k!=i || l!=j) && (plateau->getGameMatrix()[k][l]==0)){ //on the board && not the same position && empty
              plateau->addNewPawn(k,l,turn); //adding the pawn on this position
              int tmp = turnMaxPhase3(plateau, p-1, alpha, beta, startX, startY, endX, endY, player, (turn%2)+1);
              if(tmp<u){ //min
                startActionX = i;
                startActionY = j;
                endActionX = k;
                endActionY = l;
                u = tmp;
              }

              if(u<=alpha){ //cut branches
                startX = startActionX;
                startY = startActionY;
                endX = endActionX;
                endY = endActionY;
                plateau->addNewPawn(k,l,0);
                plateau->addNewPawn(i,j,turn);
                return u;
              }

              if(beta>u)
                beta=u;

              plateau->addNewPawn(k,l,0); // deleting the pawn for the next steps
            }
          }
        }
        plateau->addNewPawn(i,j,turn); // replacing the pawn for the next steps
      }
    }
  }

  startX = startActionX;
  startY = startActionY;
  endX = endActionX;
  endY = endActionY;
  return u;
}



//Estimate the score of a player by searching certain pawns' patterns
int MinMax::eval(vector<vector<int>> gameMatrix, int player) {
  int score1 = 0;
  int score2 = 0;
  int tmp1 = 0;
  int tmp2 = 0;
  int score = 0;

  for(int x=0; x<5; x++) {
    for(int y=0; y<5; y++) {
      int currentVal = gameMatrix[x][y];
      if(currentVal == 1) {
        tmp1 = findPattern(gameMatrix, x, y, 1); // test every pattern for player2
        if (tmp1 > score1) { //the max value for score1
          score1 = tmp1;
        }
      }
      if(currentVal == 2) {
        tmp2 = findPattern(gameMatrix, x, y, 2); // test every pattern for player2
        if (tmp2 > score2) { // max value for score2
          score2 = tmp2;
        }
      }
    }
  }

  if(player == 1) {
    if(score1>=1000) {
      score = score1; //win of player1
    } else if(score2>=1000) {
      score = -score2; //win of player2
    } else {
      score = score1 - score2;
    }
  } else { //if(player == 2)
    if(score2>=1000) {
      score = score2; //win of player1
    } else if(score1>=1000) {
      score = -score1; //win of player2
    } else {
      score = score2 - score1;
    }
  }
  return score;
}

//define the patterns and call testAPattern for all of them
int MinMax::findPattern(vector<vector<int>> gameMatrix, int x, int y, int player) {
  int nbPattern4 = 4;
  int pattern4[nbPattern4][4][2]  = {
    {{1000,0}, {1,1},{2,2},{3,3}}, //diag
    {{1000,0}, {1,0},{0,1},{1,1}}, //square
    {{1000,0}, {0,1},{0,2},{0,3}}, //collumn
    {{1000,0}, {1,0},{2,0},{3,0}}}; //line


  int nbPattern3 = 5;
  int pattern3[nbPattern3][3][2] = {
    {{100,0},  {1,0},{1,1}}, //square1
    {{100,0},  {0,1},{1,1}}, //square2
    {{100,0},  {1,0},{2,0}}, //line
    {{100,0},  {0,1},{0,2}}, //collumn
    {{100,0},  {1,1},{2,2}}}; //diag

  int nbPattern2 = 3;
  int pattern2[nbPattern2][2][2] = {
    {{10,0}, {1,1}}, //diag
    {{10,0}, {0,1}}, //collumn
    {{10,0}, {1,0}}}; //line

//calling testAPAttern for every pattern
int tmp;
for( int pat=0; pat<nbPattern4; pat++) {
  if ((tmp = testAPattern(gameMatrix, 4, pattern4[pat], x, y, player)) >= 0) {
    return pattern4[pat][0][0] + tmp; //stop if a pattern4 is found
  }
}
for( int pat=0; pat<nbPattern3; pat++) {
  if ((tmp = testAPattern(gameMatrix, 3, pattern3[pat], x, y, player)) >= 0) {
    return pattern3[pat][0][0] + tmp;//stop if a pattern3 is found
  }
}
  for( int pat=0; pat<nbPattern2; pat++) {
    if ((tmp = testAPattern(gameMatrix, 2, pattern2[pat], x, y, player)) >= 0) {
      return pattern2[pat][0][0] + tmp;
    }
  }
return 0;
}

//check if the given pattern is at the given coordinates and return bonus points
int MinMax::testAPattern(vector<vector<int>> gameMatrix, int patternRank, int pattern[][2], int x, int y, int player)
{
  bool testBool = true;
  int coord = 1;
  int center = 0;

  if (x == 2 && y == 2){ //add bonus points if the first pawn is in the midlle of the board
    center += 2;
  } else if (x > 0 && x < 4 && y > 0 && y < 4){
    center += 1;
  }
  do {
    int testX = x+pattern[coord][0];
    int testY = y+pattern[coord][1];
    if(testX<0 || testX>=5 || testY<0 || testY>=5) { //if we're outside of the gameMatrix
      testBool = false;
    } else {
      if(gameMatrix[testX][testY] != player) {
        testBool = false;
      }
      if (testX == 2 && testY == 2){
        center += 2;
      } else if (testX > 0 && testX < 4 && testY > 0 && testY < 4){
        center += 1;
      }
    coord++;
  }
  } while(testBool && coord <patternRank);

  if(testBool) {
    return center;
  }
  testBool = true;
  coord = 1;
  center = 0;

  if (x == 2 && y == 2){//bonus points for each pawn in the middle
    center += 2;
  } else if (x > 0 && x < 4 && y > 0 && y < 4){
    center += 1;
  }

  do {
    int testX = x-pattern[coord][0];
    int testY = y+pattern[coord][1];
    if(testX<0 || testX>=5 || testY<0 || testY>=5) { //if we're outside of the gameMatrix
      testBool = false;
    } else {
      if(gameMatrix[testX][testY] != player) { //check if ally pawn is on pattern's coordinates
        testBool = false;
      }
      if (testX == 2 && testY == 2){
        center += 2;
      } else if (testX > 0 && testX < 4 && testY > 0 && testY < 4){
        center += 1;
      }
    coord++;
  }
  } while(testBool == true && coord <patternRank);

  if(testBool == true) {
    return center; //return the amount of bonus points when pattern found
  }

return -1; //pattern isn't at this coordinates
}
