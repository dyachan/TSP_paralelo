/*
 * Rutas.h
 */

#ifndef RUTAS_H_
#define RUTAS_H_

class Rutas
{
  private:
    float *X;
    float *Y;
    int **rutas;

    void agregarARuta(int ruta, int posicion, int ciudad);
    int obtenerDeRuta(int ruta, int posicion);
    float distancia(int origen, int destino);
    bool enRuta(int ciudad, int ruta);
    /**
     * busca la ciudad mas cercana de o que no este en la lista tabu. En caso de no haber ciudades
     * disponibles retorna -1.
     */
    int masCercano(int origen, int tabu);
    bool revisarRuta(int ruta);

  public:
    int cantidad;

    Rutas(int max = 0);
    ~Rutas();

    /**
     * genera la ruta de las rutas inicio hasta fin, incluyenco inicio y excluyendo fin.
     */
    void generarRutas(int inicio = 0, int fin = -1);

    float costoRuta(int ruta);

    int rutaMenor();

    void mostrarRuta(int ruta);
};

#endif /* RUTAS_H_ */
