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

int MinMax::eval(vector<vector<int>> matrix, int player){
  return 0;
}
