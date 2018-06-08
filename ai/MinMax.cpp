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

      cout << "minMax move phase2 : " <<  x << " " <<  y << endl;

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

      cout << "minMax move phase 3 : " <<  startX << " " <<  startY << " " << endX << " " << endY << endl;

      move.push_back(startX);
      move.push_back(startY);
      move.push_back(endX);
      move.push_back(endY);
    }
        break;
  }

  return move;
}

int MinMax::turnMaxPhase2(Plateau* plateau, int p, int &alpha, int &beta, int &x, int &y, int player, int turn){
  /*int ev = eval(plateau->getGameMatrix(), player);
  cout << "Turn max, eval = " << ev << endl;
  for(int i=0; i<5; i++){
    for(int j=0; j<5 ;j++){
      cout << plateau->getGameMatrix()[i][j] << " ";
    }
    cout << endl;
  }*/


  if(plateau->hasSomeoneWon() || p==0){
    int tmp=eval(plateau->getGameMatrix(), player);
    return tmp;
  }

  if(plateau->nbPawns()==8){
    //TODO phase 3
    return turnMaxPhase2(plateau, p-1, alpha, beta, x, y, player, turn);
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
          /*
          int ev = eval(plateau->getGameMatrix(), player);
          cout << "Turn min, eval = " << ev << endl;
          for(int i=0; i<5; i++){
            for(int j=0; j<5 ;j++){
              cout << plateau->getGameMatrix()[i][j] << " ";
            }
            cout << endl;
          }
          cout << endl;*/
          //cout << "MAX u=tmp  " << u << " " << *alpha << endl;
        }
        plateau->addNewPawn(i,j,0);

        if(u>beta){ //cut branches
          x = actionX;
          y = actionY;
          //cout << "cut branches max move : " <<  *x << " " <<  *y << endl;
          return u;
        }

        if(alpha<u)
          alpha=u;
      }
    }
  }

  x = actionX;
  y = actionY;
  //cout << "end max move : " <<  *x << " " <<  *y << endl;
  return u;
}

int MinMax::turnMinPhase2(Plateau* plateau, int p, int &alpha, int &beta, int &x, int &y, int player, int turn){
  /*int ev = eval(plateau->getGameMatrix(), player);
  cout << "Turn min, eval = " << ev << endl;
  for(int i=0; i<5; i++){
    for(int j=0; j<5 ;j++){
      cout << plateau->getGameMatrix()[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl;*/


  if(plateau->hasSomeoneWon() || p==0){
    int tmp=eval(plateau->getGameMatrix(), player);
    //cout << "NB pawns = " << plateau->nbPawns() << endl;
    //cout << "MIN eval = " << tmp << endl;
    return tmp;
  }

  if(plateau->nbPawns()==8){
    //TODO phase 3
    return turnMinPhase2(plateau, p-1, alpha, beta, x, y, player, turn);
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
          /*
          int ev = eval(plateau->getGameMatrix(), player);
          cout << "Turn max, eval = " << ev << endl;
          for(int i=0; i<5; i++){
            for(int j=0; j<5 ;j++){
              cout << plateau->getGameMatrix()[i][j] << " ";
            }
            cout << endl;
          }
          cout << endl;*/
          //cout << "MIN u=tmp  " << u << " " << *beta << endl;
        }
        plateau->addNewPawn(i,j,0);

        if(u<alpha){ //cut branches
          x = actionX;
          y = actionY;
          //cout << "cut branches min move : " <<  *x << " " <<  *y << endl;
          return u;
        }

        if(beta>u)
          beta=u;
      }
    }
  }

  x = actionX;
  y = actionY;
  //cout << "end min move : " <<  *x << " " <<  *y << endl;
  return u;
}

int MinMax::turnMaxPhase3(Plateau* plateau, int p, int &alpha, int &beta, int &startX, int &startY, int &endX, int &endY, int player, int turn){

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

        //TODO ici le pion est supprimé car on test le mouvement d'un pion (#phase3)
        //seulement si le pion est supprimé de la matrice de jeu,
        //lors du turnMinPhase3, on refait une boucle sur i,j et sur k,l et cet emplacement est vide
        //donc plateau->getGameMatrix()[k][l]==0 peut retourner vrai sur lemplacement du pion
        //qu'on vient de supprimer et l'algo peut donc dire que le meilleur mouvement c'est
        //de mettre le pion à cet endroit --> trouver une solution nous devons

        for(int k=i-1; k<i+2; k++){ //checking the positions around the founded pawn
          for(int l=j-1; l<j+2; l++){
            if(k>=0 && k<5 && l>=0 && l<5 && k!=i && l!=j && (plateau->getGameMatrix()[k][l]==0)){ //on the board && empty
              plateau->addNewPawn(k,l,turn); //adding the pawn on this position
              int tmp = turnMinPhase3(plateau, p-1, alpha, beta, startX, startY, endX, endY, player, (turn%2)+1);
              if(tmp>u){ //max
                startActionX = i;
                startActionY = j;
                endActionX = k;
                endActionY = l;
                u = tmp;
              }

              if(u>beta){ //cut branches
                startX = startActionX;
                startY = startActionY;
                endX = endActionX;
                endY = endActionY;
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
  //cout << "end max move : " <<  *x << " " <<  *y << endl;
  return u;
}

int MinMax::turnMinPhase3(Plateau* plateau, int p, int &alpha, int &beta, int &startX, int &startY, int &endX, int &endY, int player, int turn){

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
              if(k>=0 && k<5 && l>=0 && l<5 && k!=i && l!=j && (plateau->getGameMatrix()[k][l]==0)){ //on the board && not the same position && empty
                plateau->addNewPawn(k,l,turn); //adding the pawn on this position
                int tmp = turnMinPhase3(plateau, p-1, alpha, beta, startX, startY, endX, endY, player, (turn%2)+1);
                if(tmp<u){ //min
                  startActionX = i;
                  startActionY = j;
                  endActionX = k;
                  endActionY = l;
                  u = tmp;
                }

                if(u<alpha){ //cut branches
                  startX = startActionX;
                  startY = startActionY;
                  endX = endActionX;
                  endY = endActionY;
                  return u;
                }

                if(beta>u)
                  alpha=u;

                plateau->addNewPawn(k,l,0); // deleting the pawn for the next steps
              }
            }
          }
          plateau->addNewPawn(i,j,turn); // replacing the pawn for the next steps
        }
      }
    }
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
