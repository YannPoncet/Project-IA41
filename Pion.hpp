#ifndef PION_H
#define PION_H

#include<iostream>

using namespace std;

class Pion{
  private: //ces attributs ne sont visibles que dans la classe Pion
    int posX; //position du pion en X
    int posY; //position du pion en Y
    int color; //pour l'instant 0 = blanc et 1 = noir

  private: //ces attributs sont visible dans la classe Pion et dans leurs descendants

  public: //ces attributs sont visibles partout
    Pion(){}; //constructeur par défaut
    Pion(int x, int y, int color); //constructeur avec des attributs
    ~Pion(){}; //destructeur, surtout utile si on attribue de la mémoire

    /**fonction move qui déplace le pion en posX+x, posY+y si possible (x et y valent -1,0 ou 1)
    * on vérifie que le pion ne sort pas du plateau dans la classe Game donc pas besoin de vérifier ici
    */
    void move(int x, int y);
};

#endif
