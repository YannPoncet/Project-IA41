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
        result = findPattern(gameMatrix, x, y, 1);
      }
      if(secondTested && currentVal == 2) {
        result = findPattern(gameMatrix, x, y, 2);
      }
    }
  }

  if(player == 1) {
    score = score1 - score2;
  } else {
    score = score2 - score1;
  }

  return score;
}

vector<int> MinMax::findPattern(vector<vector<int>> gameMatrix, int x, int y, int player) {
  std::unordered_map<int, int[3][2]> pattern4 = {
    {100, {{1,1},{2,2},{3,3}} }, //diag
    {100, {{1,0},{0,1},{1,1}} }, //square
    {100, {{1,0},{2,0},{3,0}} }}; //line
  std::unordered_map<int, int[2][2]> pattern3 = {
    {10, {{1,0},{1,1}} }, //square
    {10, {{1,0},{2,0}} }, //line
    {10, {{1,1},{2,2}} }}; //diag
  std::unordered_map<int, int[1][2]> pattern2 = {
    {1, {{1,1}} }, //diag
    {1, {{1,0}} }}; //line


  vector<int> result;

  /*for(int pat=0; pat<(signed)pattern4.size(); pat++) {
    bool testBool = true;
    int coord = 0;
    do {
      int testX = x+pattern4[pat][coord][0];
      int testY = y+pattern4[pat][coord][1];
      if(testX>=0 && testX<this->nbCells && testY>=0 && testY<this->nbCells) { //if we're outside of the gameMatrix
        if(this->gameMatrix[testX][testY] != currentVal) {
          testBool = false;
        }
      } else {
        testBool = false;
      }
      coord++;
    } while(testBool == true && coord <3);

    if(testBool == true) { //if test bool is still at true, we have found a victory configuration
      return currentVal;
    }
  }

*/
  return {0,0};
}

/*bool testAPattern(vector<vector<int>> gameMatrix, int x, int y, int player)
{

}
*/
