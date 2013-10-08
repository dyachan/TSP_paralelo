/*
 * Main.cpp
 */

#include <stdlib.h>
#include <iostream>

#include "Rutas.h"

int main(int argc, char* argv[])
{
  using namespace Rutas;
  if(argc > 1)
    iniciar(atoi(argv[1]));
  else
    iniciar();

  generarRutas(0, 10);
//  mostrarRutas();
  finalizar();
  return 0;
}
