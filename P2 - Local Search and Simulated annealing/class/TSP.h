#ifndef TSP_H_
#include <iostream>
#define TSP_H_


#include "Problema.h"

namespace clases {

struct datosInstanciaTSP{
	// Decidir que tiene!
	int m;
	float ** matriz;
};

struct datosSolucionTSP{
	// Decidir que tiene!
	int * soluciones;
};

class TSP: public clases::Problema<struct datosInstanciaTSP,struct datosSolucionTSP> {

public:
	TSP();
	virtual ~TSP();
	int tamano();
	int leerInstancia(char * archivo);
	float evaluarSolucion(struct datosSolucionTSP* sol);
	float evaluarSolucion2(struct datosSolucionTSP *sol,int valor,int w,int p);
	struct datosSolucionTSP * generarSolucionRandom();
	void imprimirSolucion(struct datosSolucionTSP * sol);
	void imprimirInstancia();
	void liberarMemoriaSolucion(struct datosSolucionTSP *sol);
	struct datosSolucionTSP * generarVecindario(datosSolucionTSP * sol, int vecino, int j);
    struct datosSolucionTSP * aplicarBusquedaLocal(struct datosSolucionTSP *sol, bool firstImprovement);
	struct datosSolucionTSP * aplicarEnfriamientoSimulado(struct datosSolucionTSP *sol, float tFinal, float alpha);
private:
	int reservarMemoria();
	void liberarMemoria();
};

}

#endif /* TSP_H_ */
