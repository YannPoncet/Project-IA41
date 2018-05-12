
#include "Pion.hpp"

//on met Pion:: pour dire qu'on travaille dans la classe Pion
Pion::Pion(int x, int y, int color) {
  posX = x;
  posY = y;

  /**ici on peut confondre l'attribut "color" de la classe Pion et l'attribut "color" passé en parametre
  * on utilise donc this-> (oui c'est un pointeur donc on a une fleche)
  * pour dire que c'est l'attribut color de la classe Pion (this = la classe Pion)
  */
  this->color = color;
}

void Pion::move(int x, int y) {
  posX += x;
  posY += y;
}
