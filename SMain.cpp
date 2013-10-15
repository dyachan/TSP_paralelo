/*
 * Main.cpp
 */

#include <stdlib.h>
#include <iostream>

#include "Rutas.h"

int main(int argc, char* argv[])
{
  Rutas *r;
  if(argc > 1)
  {
    r = new Rutas(atoi(argv[1]));
    r->generarRutas();
  }
  else
  {
    r = new Rutas();
    r->generarRutas();
  }
/*
  for(int i = 0; i < r->cantidad; i++)
  {
    std::cout << "ruta " << i << ": ";
    r->mostrarRuta(i);
    std::cout << " costo " << r->costoRuta(i) << std::endl;
  }
*/
  int m = r->rutaMenor();
  std::cout << "la ruta menor es " << m << " con un costo de " << r->costoRuta(m) << std::endl;
  std::cout << "con la ruta: ";
  r->mostrarRuta(m);
  std::cout << std::endl;

  delete r;
  return 0;
}
