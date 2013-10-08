/*
 * Rutas.h
 */

#ifndef RUTAS_H_
#define RUTAS_H_

#include <vector>

namespace Rutas
{
    extern int cantidad;

    void iniciar(int max = 0);
    void finalizar();

    void generarRutas(int inicio, int fin = -1);

    float costoRuta(int ruta);

    int rutaMenor();
};

#endif /* RUTAS_H_ */
