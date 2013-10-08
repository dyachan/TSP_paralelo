/*
 * Rutas.cpp
 */

#include <iostream>
#include <math.h>

#include "Rutas.h"

namespace Rutas
{
  namespace // entidades privadas
  {
//    int cantidad;
    float *X;
    float *Y;

    int **rutas;

    void agregarARuta(int ruta, int posicion, int ciudad)
    {
      rutas[ruta][posicion] = ciudad;
    }

    int obtenerDeRuta(int ruta, int posicion)
    {
      return rutas[ruta][posicion];
    }

    float distancia(int o, int d)
    {
      return sqrt(pow(X[o] - X[d], 2) + pow(Y[o] - Y[d], 2));
    }

    bool enRuta(int c, int ruta)
    {
      int en = false;
      for(int i = 0; i < cantidad; i++)
        if(obtenerDeRuta(ruta, i) == c)
        {
          en = true;
          break;
        }
      return en;
    }

    /**
     * busca la ciudad mas cercana de o que no este en la lista tabu. En caso de no haber ciudades
     * disponibles retorna -1.
     */
    int masCercano(int o, int tabu)
    {
      // encontrar la primera ciudad disponible para comenzar a iterar
      int cercano = -1;
      for(int c = 0; c < cantidad; c++)
        if(!enRuta(c, tabu))
        {
          cercano = c;
          break;
        }

      if(cercano != -1)
      {
        int costoMenor = distancia(o, cercano);

        // iterar en el resto de las ciudades posibles para buscar mas cercano
        for(int c = 0; c < cantidad; c++)
          if( !enRuta(c, tabu) && (costoMenor > distancia(o, c)) )
          {
            costoMenor = distancia(o, c);
            cercano = c;
          }
      }

      return cercano;
    }
  }

  // entidades publicas

  int cantidad;

  void iniciar(int max)
  {
    std::cin >> cantidad;
    if(max != 0)
      cantidad = max;
    X = new float[cantidad];
    Y = new float[cantidad];
    for(int i = 0; i < cantidad; i++)
      std::cin >> X[i] >> Y[i];

    rutas = new int*[cantidad];
    for(int r = 0; r < cantidad; r++)
      rutas[r] = new int[cantidad];
  }

  void finalizar()
  {
    delete[] X;
    delete[] Y;

    for(int r = 0; r < cantidad; r++)
      delete[] rutas[r];
    delete[] rutas;
  }

  void generarRutas(int inicio, int fin)
  {
    if(fin == -1)
      fin = cantidad;
    for(int i = inicio; i < fin; i++)
    {
//      std::cout << i;
      agregarARuta(i, 0, i);
      for(int s = 1; s < cantidad; s++)
        agregarARuta(i, s, masCercano(obtenerDeRuta(i, s-1), i) );
    }
  }

  float costoRuta(int ruta)
  {
    float costo = distancia(obtenerDeRuta(ruta, cantidad-1), obtenerDeRuta(ruta, 0));
    for(int c = 1; c < cantidad; c++)
      costo += distancia(obtenerDeRuta(ruta, c-1), obtenerDeRuta(ruta, c));
    std::cout << "para ruta " << ruta << " el costo es " << costo << std::endl;
    return costo;
  }

  int rutaMenor()
  {
    int r_menor = 0;
    int c_menor = costoRuta(r_menor);
    for(int r = 1; r < cantidad; r++)
      if(costoRuta(r) < c_menor)
      {
        r_menor = r;
        c_menor = costoRuta(r_menor);
      }
    return r_menor;
  }

}
