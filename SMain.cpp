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
    generarRutas(0);
  }
  else
  {
    iniciar();
    generarRutas(0);
  }

//  for(int i = 0; i < cantidad; i++)
//    costoRuta(i);
  int m = rutaMenor();
  std::cout << "la ruta menor es " << m << std::endl;
  std::cout << "con la ruta: ";
  mostrarRuta(m);
  std::cout << std::endl;

  finalizar();
  return 0;
}
