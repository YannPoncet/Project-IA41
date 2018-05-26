#include "MinMax.hpp"

vector<int> MinMax::phase2(Plateau* plateau, int player, int turn){
  vector<int> finalDecision;

  // an array to collect all the possible move
  vector<vector<int>> moves;
  miniMax(moves, plateau, player, turn,1);
  cout<<"end of miniMax"<<endl;
  
// if it is the computer's turn loop over the moves and choose the move with the highest score
  if(player == turn){
    int bestScore = -10000;
    for(unsigned int i = 0; i < moves.size(); i++){
      if(moves[i][0] > bestScore){ //[0] = score
        bestScore = moves[i][0];
        finalDecision[0] = moves[i][1]; //x
        finalDecision[1] = moves[i][2]; //y
      }
    }
  }else{

// else loop over the moves and choose the move with the lowest score
    int bestScore = 10000;
    for(unsigned int i = 0; i < moves.size(); i++){
      if(moves[i][0] < bestScore){
        bestScore = moves[i][0];
        finalDecision[0] = moves[i][1]; //x
        finalDecision[1] = moves[i][2]; //y
      }
    }
  }

  return finalDecision;
}

int MinMax::miniMax(vector<vector<int>> moves, Plateau* plateau, int player, int turn, int iteration){

  cout<<iteration<<endl;
  iteration++;

  // loop through available spots
  for (unsigned int i = 0; i < plateau->getGameMatrix().size(); i++){
    for (unsigned int j = 0; j < plateau->getGameMatrix()[i].size(); j++){
      if(plateau->getGameMatrix()[i][j]==0){ //available spot

        //create an object for each and store the index of that spot
        vector<int> move;
      	move.push_back(0);
        move.push_back(i);
        move.push_back(j);

        // set the empty spot to the current player
        plateau->getGameMatrix()[i][j] = turn;

        /*collect the score resulted from calling minimax
          on the opponent of the current player*/
        if (player == turn){
          int result = miniMax(moves, plateau, player, (turn%2)+1, iteration);
          move[0] = result;
        }
        else{
          int result = miniMax(moves, plateau, player, (turn%2)+1, iteration);
          move[0] = result;
        }

        // reset the spot to empty
        plateau->getGameMatrix()[i][j] = 0;

        // push the object to the array
        moves.push_back(move);
      }
    }
  }

  // checks for the terminal states such as win, lose, and tie
  //and returning a value accordingly
  return winning(plateau, player)*10;
}

int MinMax::winning(Plateau* plateau, int player){
  if(plateau->hasSomeoneWon()==player)
    return 1;
  else if(plateau->hasSomeoneWon()==(player%2)+1)
    return -1;
  return 0;
}
