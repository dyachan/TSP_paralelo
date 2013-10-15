/*
 * Main.cpp
 */

#include <stdlib.h>
#include <iostream>
#include <pthread.h>

#include "Rutas.h"

typedef struct
{
  int id;
  int inicio;
  int final;
  Rutas *rutas;
}Parametro;

void *trabajoHilo(Parametro p);
int generarParalelo(int cantRutas, Rutas *r);

int main(int argc, char* argv[])
{
  Rutas *r;
  if(argc > 2)
    r = new Rutas(atoi(argv[2]));
  else
    r = new Rutas();

  generarParalelo(atoi(argv[1]), r);


//  for(int i = 0; i < cantidad; i++)
//    costoRuta(i);
  int m = r->rutaMenor();
  std::cout << "la ruta menor es " << m << " con un costo de " << r->costoRuta(m) << std::endl;
  std::cout << "con la ruta: ";
  r->mostrarRuta(m);
  std::cout << std::endl;

  delete r;
  return 0;
}

void *trabajoHilo(void *p)
{
  Parametro *params = (Parametro *) p;
//  std::cout << "hilo " << params->id << " de " << params->inicio << " a " << params->final << std::endl;
  params->rutas->generarRutas(params->inicio, params->final);
  /*
  for(int r = params->inicio; r < params->final; r++)
  {
    std::cout << "ruta " << r << ": ";
    params->rutas->mostrarRuta(r);
    std::cout << std::endl;
  }
  */
  pthread_exit(0);
}

int generarParalelo(int cr, Rutas *r)
{
  int cantHilos = r->cantidad / cr + 1;
  if(r->cantidad % cr == 0)
    cantHilos--;
//  std::cout << "hilos a crear: " << cantHilos << std::endl;
  pthread_t *hilos = new pthread_t[cantHilos];
  Parametro *p = new Parametro[cantHilos];

  for(int h = 0; h < cantHilos; h++)
  {
    p[h].id = h;
    p[h].inicio = cr * h;
    p[h].final = cr * (h+1);
    if(p[h].final > r->cantidad)
      p[h].final = r->cantidad;
    p[h].rutas = r;
    pthread_create(&hilos[h], NULL, trabajoHilo, &p[h]);
  }

  for(int h = 0; h < cantHilos; h++)
    pthread_join(hilos[h], NULL);

  delete[] p;
}
