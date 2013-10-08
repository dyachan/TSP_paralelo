/*
 * Rutas.cpp
 */

#include <iostream>
#include <math.h>

#include "Rutas.h"

namespace Rutas
{
  namespace
  {
    int cantidad;
    float *X;
    float *Y;

    std::vector< std::vector<int> > rutas;
  }

  void iniciar(int max)
  {
    std::cin >> cantidad;
    if(max != 0)
      cantidad = max;
    X = new float[cantidad];
    Y = new float[cantidad];
    for(int i = 0; i < cantidad; i++)
      std::cin >> X[i] >> Y[i];

    rutas.resize(cantidad);
    for(int r = 0; r < cantidad; r++)
      rutas[r].resize(cantidad, -1);
  }

  void finalizar()
  {
    delete[] X;
    delete[] Y;
  }

  void mostrarPosicion(int i)
  {
    std::cout << "ciudad " << i << " en x=" << X[i] << ", y=" << Y[i] << std::endl;
  }

  float distancia(int o, int d)
  {
    return sqrt(pow(X[o] - X[d], 2) + pow(Y[o] - Y[d], 2));
  }

  void mostrarDistancia(int o, int d)
  {
    std::cout << "entre ciudad " << o << " y  ciudad " << d << " hay una distancia de " << distancia(o, d) << std::endl;
  }

  bool enRuta(int c, std::vector<int> ruta)
  {
    int en = false;
    for(std::vector<int>::iterator it = ruta.begin(); *it != -1; ++it)
      if(*it == c)
      {
        en = true;
        break;
      }
    return en;
  }

  int masCercano(int o, std::vector<int> tabu)
  {
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

  void generarRutas(int inicio, int fin)
  {
    for(int i = inicio; i < fin; i++)
    {
      std::cout << i;
      rutas[i][0] = i;
      for(int s = 1; s < cantidad; s++)
        rutas[i][s] = masCercano(rutas[i][s-1], rutas[i]);
    }
  }

  void mostrarRutas()
  {
    for(int r = 0; r < cantidad; r++)
    {
      std::cout << "para ruta " << r ;//<< std::endl;
/*      for(int c = 0; c < cantidad; c++)
      {
        std::cout << rutas[r][c] << ".";
      }
*/      std::cout << " con costo de " << costoRuta(rutas[r]) << std::endl;

    }
  }

  float costoRuta(std::vector<int> ruta)
  {
    float costo = distancia(ruta[cantidad-1], ruta[0]);
    for(int c = 1; c < cantidad; c++)
      costo += distancia(ruta[c-1], ruta[c]);
    return costo;
  }

}
