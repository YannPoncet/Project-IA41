#include "MinMax.hpp"

vector<int> MinMax::minMax(Plateau* plateau, int profondeur, int player, int turn){

  int x = -1;
  int y = -1;
  int* px = &x;
  int* py = &y;

  int alpha = std::numeric_limits<int>::min();
  int beta = std::numeric_limits<int>::max();
  int* a = &alpha;
  int* b = &beta;

  turnMax(plateau, profondeur, a, b, px, py, player, turn);

  cout << "minMax move : " <<  x << " " <<  y << endl;

  vector<int> move;
  move.push_back(x); //x
  move.push_back(y); //y
  return move;
}

int MinMax::turnMax(Plateau* plateau, int p, int* alpha, int* beta, int* x, int* y, int player, int turn){
  if(plateau->hasSomeoneWon() || p==0)
    return eval(plateau->getGameMatrix(), player);

  int u = std::numeric_limits<int>::min();
  int actionX = -1;
  int actionY = -1;

  for(int i=0; i<5; i++){
    for(int j=0; j<5 ;j++){
      if(plateau->getGameMatrix()[i][j]==0){ //case vide
        plateau->addNewPawn(i,j,turn);
        if(int tmp = turnMin(plateau, p-1, alpha, beta, x, y, player, turn)>u){ //max
          actionX = i;
          actionY = j;
          u = tmp;
          cout << "MAX u=tmp  " << u << " " << *alpha << endl;
        }
        plateau->addNewPawn(i,j,0);

        if(u>*beta){ //cut branches
          *x = actionX;
          *y = actionY;
          cout << "cut branches max move : " <<  *x << " " <<  *y << endl;
          return u;
        }

        if(*alpha<u)
          *alpha=u;
      }
    }
  }

  *x = actionX;
  *y = actionY;
  cout << "end max move : " <<  *x << " " <<  *y << endl;
  return u;
}

int MinMax::turnMin(Plateau* plateau, int p, int* alpha, int* beta, int* x, int* y, int player, int turn){
  if(plateau->hasSomeoneWon() || p==0)
    return eval(plateau->getGameMatrix(), player);

  int u = std::numeric_limits<int>::max();
  int actionX = -1;
  int actionY = -1;

  for(int i=0; i<5; i++){
    for(int j=0; j<5 ;j++){
      if(plateau->getGameMatrix()[i][j]==0){ //case vide
        plateau->addNewPawn(i,j,turn);
        if(int tmp = turnMax(plateau, p-1, alpha, beta, x, y, player, turn)<u){ //max
          actionX = i;
          actionY = j;
          u = tmp;
          //cout << "MIN u=tmp  " << u << " " << *beta << endl;
        }
        plateau->addNewPawn(i,j,0);

        if(u<*alpha){ //cut branches
          *x = actionX;
          *y = actionY;
          cout << "cut branches min move : " <<  *x << " " <<  *y << endl;
          return u;
        }

        if(*beta>u)
          *beta=u;
      }
    }
  }

  *x = actionX;
  *y = actionY;
  cout << "end min move : " <<  *x << " " <<  *y << endl;
  return u;
}


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
        tmp1 = findPattern(gameMatrix, x, y, 1);
        if (tmp1 > score1) {
          score1 = tmp1;
        }
      }
      if(currentVal == 2) {
        tmp2 = findPattern(gameMatrix, x, y, 2);
        if (tmp2 > score2) {
          score2 = tmp2;
        }
      }
    }
  }

  if(player == 1 && score1>=100) {
    score = score1;
  } else if(player == 1) {
    score = score1 - score2;
  } else if(player == 2 && score2>=100) {
    score = score2;
  } else if(player == 2) {
    score = score2 - score1;
  }
//printf("Score player1 :%d\n",score);
  return score;
}

int MinMax::findPattern(vector<vector<int>> gameMatrix, int x, int y, int player) {
  int nbPattern4 = 4;
  int pattern4[nbPattern4][4][2]  = {
  //{{score,0}},  {X1,Y1},{X2,Y2},{X3,Y3}}}
    {{100,0}, {1,1},{2,2},{3,3}}, //diag
    {{100,0}, {1,0},{0,1},{1,1}}, //square
    {{100,0}, {0,1},{0,2},{0,3}}, //collumn
    {{100,0}, {1,0},{2,0},{3,0}}, //line

    {{50,0}, {1,0},{2,1},{3,2}}, //L1
    {{50,0}, {0,1},{2,3},{3,4}}}; //L2

  int nbPattern3 = 4;
  int pattern3[nbPattern3][3][2] = {
    {{10,0},  {1,0},{1,1}}, //square1
    {{10,0},  {0,1},{1,1}}, //square2
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
