/*
 * Main.cpp
 */

#include <stdlib.h>
#include <iostream>
#include <pthread.h>

#include "Rutas.h"

typedef struct
{
  int inicio;
  int final;
}Parametro;

void *trabajoHilo(Parametro p);
int generarParalelo(int cantRutas);

int main(int argc, char* argv[])
{
  using namespace Rutas;
  if(argc > 2)
    iniciar(atoi(argv[2]));
  else
    iniciar();

  generarParalelo(atoi(argv[1]));

//  for(int i = 0; i < cantidad; i++)
//    costoRuta(i);
  int m = rutaMenor();
  std::cout << "la ruta menor es " << m << " con un costo de " << Rutas::costoRuta(m) << std::endl;
  std::cout << "con la ruta: ";
  mostrarRuta(m);
  std::cout << std::endl;

  finalizar();
  return 0;
}

void *trabajoHilo(void *p)
{
  Parametro *params = (Parametro *) p;
  Rutas::generarRutas(params->inicio, params->final);
//  std::cout << "hilo con i: " << params->inicio << " y f: " << params->final << std::endl;
  pthread_exit(0);
  return NULL;
}

int generarParalelo(int cr)
{
  int cantHilos = Rutas::cantidad / cr + 1;
  if(Rutas::cantidad % cr == 0)
    cantHilos--;
  std::cout << "hilos a crear: " << cantHilos << std::endl;
  pthread_t *hilos = new pthread_t[cantHilos];
  Parametro *p = new Parametro[cantHilos];

  for(int h = 0; h < cantHilos; h++)
  {
    p[h].inicio = cr * h;
    p[h].final = cr * (h+1) - 1;
    if(p[h].final > Rutas::cantidad)
      p[h].final = Rutas::cantidad;
    pthread_create(&hilos[h], NULL, trabajoHilo, &p[h]);
  }

  for(int h = 0; h < cantHilos; h++)
    pthread_join(hilos[h], NULL);

  delete[] p;
}
