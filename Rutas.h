/*
 * Rutas.h
 */

#ifndef RUTAS_H_
#define RUTAS_H_

namespace Rutas
{
    extern int cantidad;

    void iniciar(int max = 0);
    void finalizar();

    /**
     * genera la ruta de las rutas inicio hasta fin, incluyenco inicio y excluyendo fin.
     */
    void generarRutas(int inicio, int fin = -1);

    float costoRuta(int ruta);

    int rutaMenor();

    void mostrarRuta(int ruta);
};

#endif /* RUTAS_H_ */
