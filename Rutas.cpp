/*
 * Rutas.cpp
 */

#include <iostream>
#include <math.h>
#include <string.h>

#include "Rutas.h"

/**************************/
/*** entidades privadas ***/
/**************************/

void Rutas::agregarARuta(int ruta, int posicion, int ciudad)
{
  this->rutas[ruta][posicion] = ciudad;
}

int Rutas::obtenerDeRuta(int ruta, int posicion)
{
  return this->rutas[ruta][posicion];
}

float Rutas::distancia(int o, int d)
{
  return sqrt(pow(this->X[o] - this->X[d], 2) + pow(this->Y[o] - this->Y[d], 2));
}

bool Rutas::enRuta(int c, int ruta)
{
  int en = false;
//  std::cout << "buscar " << c << " en lista " << ruta << std::endl;
  for(int i = 0; i < this->cantidad; i++)
  {
//    std::cout << "en " << i << " hay " << this->obtenerDeRuta(ruta, i) << std::endl;
    if(this->obtenerDeRuta(ruta, i) == c)
    {
      en = true;
      break;
    }
  }
  return en;
}

int Rutas::masCercano(int o, int tabu)
{
  // encontrar la primera ciudad disponible para comenzar a iterar
  int cercano = -1;
//  std::cout << "*" << o << " - " << tabu << std::endl;
  for(int c = 0; c < this->cantidad; c++)
    if(!this->enRuta(c, tabu))
    {
      cercano = c;
      break;
    }

  if(cercano != -1)
  {
    int costoMenor = this->distancia(o, cercano);

    // iterar en el resto de las ciudades posibles para buscar mas cercano
    for(int c = 0; c < this->cantidad; c++)
      if( !this->enRuta(c, tabu) && (costoMenor > this->distancia(o, c)) )
      {
        costoMenor = this->distancia(o, c);
        cercano = c;
      }
  }

  return cercano;
}

bool Rutas::revisarRuta(int ruta)
{
  bool bien = true;
  for(int c = 0; c < this->cantidad; c++)
    if(this->obtenerDeRuta(ruta, c) == -1)
    {
      bien = false;
      break;
    }
  return bien;
}

/**************************/
/*** entidades publicas ***/
/**************************/

Rutas::Rutas(int max)
{
  std::cin >> this->cantidad;
  if(max != 0)
    this->cantidad = max;
  this->X = new float[this->cantidad];
  this->Y = new float[this->cantidad];
  for(int i = 0; i < this->cantidad; i++)
    std::cin >> this->X[i] >> this->Y[i];

  this->rutas = new int*[this->cantidad];
  for(int r = 0; r < this->cantidad; r++)
  {
    this->rutas[r] = new int[this->cantidad];
//    memset(this->rutas[r], -1, this->cantidad);
    for(int c = 0; c < this->cantidad; c++)
      this->agregarARuta(r, c, -1);
  }
}

Rutas::~Rutas()
{
  delete[] this->X;
  delete[] this->Y;

  for(int r = 0; r < this->cantidad; r++)
    delete[] this->rutas[r];
  delete[] this->rutas;
}

void Rutas::generarRutas(int inicio, int fin)
{
  if(fin == -1)
    fin = this->cantidad;
  for(int i = inicio; i < fin; i++)
  {
    this->agregarARuta(i, 0, i);
    for(int s = 1; s < this->cantidad; s++)
      this->agregarARuta(i, s, this->masCercano(this->obtenerDeRuta(i, s-1), i) );
  }
}

float Rutas::costoRuta(int ruta)
{
  if(this->revisarRuta(ruta))
  {
    float costo = this->distancia(this->obtenerDeRuta(ruta, this->cantidad-1),
                                  this->obtenerDeRuta(ruta, 0));
    for(int c = 1; c < this->cantidad; c++)
      costo += this->distancia(this->obtenerDeRuta(ruta, c-1),
                               this->obtenerDeRuta(ruta, c));
  //    std::cout << "para ruta " << ruta << " el costo es " << costo << std::endl;
    return costo;
  }
  else
    return -1;
}

int Rutas::rutaMenor()
{
  int r_menor = 0;
  int c_menor = this->costoRuta(r_menor);
  for(int r = 1; r < this->cantidad; r++)
    if(this->costoRuta(r) < c_menor)
    {
      r_menor = r;
      c_menor = this->costoRuta(r_menor);
    }
  return r_menor;
}

void Rutas::mostrarRuta(int ruta)
{
  if(!this->revisarRuta(ruta))
    std::cout << "*";

  // buscar la primera ciudad y su continuacion
  int i = 0;
  int s = 1;
  for(int c = 0; c < this->cantidad; c++)
    if(this->obtenerDeRuta(ruta, c) == 0)
    {
      i = c;
      if(this->obtenerDeRuta(ruta, (c+1)%this->cantidad) >
         this->obtenerDeRuta(ruta, (c-1)%this->cantidad))
        s = -1;
      break;
    }

  // mostrar ruta
  for(int c = 0; c != this->cantidad && c != -this->cantidad; c += s)
    std::cout << this->obtenerDeRuta(ruta, (c+i+this->cantidad)%this->cantidad) << ".";
}
