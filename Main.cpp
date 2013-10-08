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
  {
    iniciar(atoi(argv[1]));
    generarRutas(0, atoi(argv[1]));
  }
  else
  {
    iniciar();
    generarRutas(0);
  }

  for(int i = 0; i < cantidad; i++)
    costoRuta(i);
  std::cout << "la ruta menor es " << rutaMenor() << std::endl;
  finalizar();
  return 0;
}
