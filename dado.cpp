#include "dado.h"

Dado::Dado() {srand(time(0));}
int Dado::GetValorDado() {return  (rand() % 6) + 1;}
