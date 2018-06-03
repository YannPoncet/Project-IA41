#include "MinMax.hpp"

vector<int> MinMax::minMax(Plateau* plateau, int profondeur, int player, int turn){
  vector<int> move;
  move.push_back(-1); //x
  move.push_back(-1); //y

  vector<int> alphaBeta;
  alphaBeta.push_back(std::numeric_limits<int>::min()); //alpha
  alphaBeta.push_back(std::numeric_limits<int>::max()); //beta

  tourMax(plateau, profondeur, alphaBeta, move, player, turn);

  return move;
}

int MinMax::tourMax(Plateau* plateau, int p, vector<int> alphaBeta, vector<int> move, int player, int turn){
  if(plateau->hasSomeoneWon() || p==0)
    return eval(plateau->getGameMatrix(), player);

  int u = std::numeric_limits<int>::min();
  vector<int> action;
  action.push_back(-1);
  action.push_back(-1);

  for(int i=0; i<5; i++){
    for(int j=0; j<5 ;j++){
      if(plateau->getGameMatrix()[i][j]==0){ //case vide
        plateau->getGameMatrix()[i][j] = turn;
        if(int tmp = tourMin(plateau, p-1, alphaBeta,  move, player, turn)>u){ //max
          action[0] = i;
          action[1] = j;
          u = tmp;
        }
        plateau->getGameMatrix()[i][j] = 0;

        if(u>alphaBeta[1]){ //cut branches
          move[0] = action[0];
          move[1] = action[1];
          return u;
        }

        if(alphaBeta[0]<u)
          alphaBeta[0]=u;
      }
    }
  }

  move[0] = action[0];
  move[1] = action[1];
  return u;
}

int MinMax::tourMin(Plateau* plateau, int p, vector<int> alphaBeta, vector<int> move, int player, int turn){
  if(plateau->hasSomeoneWon() || p==0)
    return eval(plateau->getGameMatrix(), player);

  int u = std::numeric_limits<int>::max();
  vector<int> action;
  action.push_back(-1);
  action.push_back(-1);

  for(int i=0; i<5; i++){
    for(int j=0; j<5 ;j++){
      if(plateau->getGameMatrix()[i][j]==0){ //case vide
        plateau->getGameMatrix()[i][j] = turn;
        if(int tmp = tourMax(plateau, p-1, alphaBeta,  move, player, turn)<u){ //max
          action[0] = i;
          action[1] = j;
          u = tmp;
        }
        plateau->getGameMatrix()[i][j] = 0;

        if(u<alphaBeta[0]){ //cut branches
          move[0] = action[0];
          move[1] = action[1];
          return u;
        }

        if(alphaBeta[1]>u)
          alphaBeta[1]=u;
      }
    }
  }

  move[0] = action[0];
  move[1] = action[1];
  return u;
}


int MinMax::eval(vector<vector<int>> gameMatrix, int player) {
  bool firstTested = true;
  bool secondTested = true;
  int score1 = 0;
  int score2 = 0;
  int score = 0;

  for(int x=0; x<5; x++) {
    for(int y=0; y<5; y++) {
      int currentVal = gameMatrix[x][y];
      vector<int> result;
      if(firstTested && currentVal == 1) {
        score1 = findPattern(gameMatrix, x, y, 1);
        if (score1 > 0) {
          firstTested = false;
        }
      }
      if(secondTested && currentVal == 2) {
        score2 = findPattern(gameMatrix, x, y, 2);
        if (score2 > 0) {
          secondTested = false;
        }
      }
    }
  }

  if(player == 1) {
    score = score1 - score2;
  } else {
    score = score2 - score1;
  }
printf("Score player1 :%d\n",score);
  return score;
}

int MinMax::findPattern(vector<vector<int>> gameMatrix, int x, int y, int player) {
  int nbPattern4 = 4;
  int pattern4[nbPattern4][4][2]  = {
  //{{score,0}},  {X1,Y1},{X2,Y2},{X3,Y3}}}
    {{100,0}, {1,1},{2,2},{3,3}}, //diag
    {{100,0}, {1,0},{0,1},{1,1}}, //square
    {{100,0}, {0,1},{0,2},{0,3}}, //collumn
    {{100,0}, {1,0},{2,0},{3,0}}}; //line

  int nbPattern3 = 4;
  int pattern3[nbPattern3][3][2] = {
    {{10,0},  {1,0},{1,1}}, //square
    {{10,0},  {1,0},{2,0}}, //line
    {{10,0},  {0,1},{0,2}}, //collumn
    {{10,0},  {1,1},{2,2}}}; //diag
  int nbPattern2 = 3;
  int pattern2[nbPattern2][2][2] = {
    {{1,0}, {1,1}}, //diag
    {{1,0}, {0,1}}, //collumn
    {{1,0}, {1,0}}}; //line

for( int pat=0; pat<nbPattern4; pat++) {
  if (testAPattern(gameMatrix, 4, pattern4[pat], x, y, player)) {
    return pattern4[pat][0][0];
  }
}
for( int pat=0; pat<nbPattern3; pat++) {
  if (testAPattern(gameMatrix, 3, pattern3[pat], x, y, player)) {
    return pattern3[pat][0][0];
  }
}
  for( int pat=0; pat<nbPattern2; pat++) {
    if (testAPattern(gameMatrix, 2, pattern2[pat], x, y, player)) {
      return pattern2[pat][0][0];
    }
  }
return 0;
}


bool MinMax::testAPattern(vector<vector<int>> gameMatrix, int patternRank, int pattern[][2], int x, int y, int player)
{
  bool testBool = true;
  int coord = 1;
  do {
    int testX = x+pattern[coord][0];
    int testY = y+pattern[coord][1];
    if(testX<0 || testX>=5 || testY<0 || testY>=5) { //if we're outside of the gameMatrix
      testBool = false;
    } else {
      if(gameMatrix[testX][testY] != player) {
        testBool = false;
      }
    coord++;
  }
  } while(testBool == true && coord <patternRank);

  if(testBool == true) {
    return true;
  }
  testBool = true;
  coord = 1;
  do {
    int testX = x-pattern[coord][0];
    int testY = y+pattern[coord][1];
    if(testX<0 || testX>=5 || testY<0 || testY>=5) { //if we're outside of the gameMatrix
      testBool = false;
    } else {
      if(gameMatrix[testX][testY] != player) {
        testBool = false;
      }
    coord++;
  }
  } while(testBool == true && coord <patternRank);

  if(testBool == true) {
    return true;
  }

return false;
}
