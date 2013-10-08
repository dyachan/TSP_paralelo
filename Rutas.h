/*
 * Rutas.h
 */

#ifndef RUTAS_H_
#define RUTAS_H_

#include <vector>

namespace Rutas
{
    void iniciar(int max = 0);
    void finalizar();
    void mostrarPosicion(int i);
    float distancia(int origen, int destino);
    void mostrarDistancia(int origen, int destino);

    bool enRuta(int c, std::vector<int> ruta);
    int masCercano(int origen, std::vector<int> tabu);

    void generarRutas(int inicio, int fin);
    void mostrarRutas();

    float costoRuta(std::vector<int> ruta);
};

#endif /* RUTAS_H_ */
