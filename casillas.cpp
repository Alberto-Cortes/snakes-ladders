#include "casillas.h"

Casillas::Casillas() {bonus = 0;}
Casillas::Casillas(int val) {bonus = val;}
int Casillas::getBonus() {return bonus;}
void Casillas::setBonus(int val) {bonus = val;}
