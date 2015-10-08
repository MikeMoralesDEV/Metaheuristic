#ifndef TSP_H_
#include <iostream>
#define TSP_H_


#include "Problema.h"

namespace mh {

struct datosInstanciaTSP{
	// Decidir que tiene!
	int m;
	float ** d;
};

struct datosSolucionTSP{
	// Decidir que tiene!
	int * x;
};

class TSP: public mh::Problema<struct datosInstanciaTSP,struct datosSolucionTSP> {

public:
	TSP();
	virtual ~TSP();
	int leerInstancia(char * archivo);
	float evaluarSolucion(struct datosSolucionTSP* sol);
	struct datosSolucionTSP * generarSolucionRandom();
	void imprimirSolucion(struct datosSolucionTSP * sol);
	void imprimirInstancia();
	void liberarMemoriaSolucion(struct datosSolucionTSP *sol);
private:
	int reservarMemoriaInstancia();
	void liberarMemoriaInstancia();
};

}

#endif /* TSP_H_ */
