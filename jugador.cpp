#include "jugador.h"

using namespace std;

Jugador::Jugador(int i, int p) {position = p; id = i;}
void Jugador::movePlayer(int val) {position = position + val;} // Legacy method.
void Jugador::setPosition(int val) {position = val;}
int Jugador::getPosition() {return position;}
int Jugador::getID() {return id;}
