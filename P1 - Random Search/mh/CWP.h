#ifndef CWP_H_
#include <iostream>
#define CWP_H_

#include "Problema.h"

namespace mh {

struct datosInstanciaCWP{
	// Decidir que tiene!
	int n;
	int m;
	int ** d;
};

struct datosSolucionCWP{
	// Decidir que tiene!
	int * x;
};

class CWP: public mh::Problema<struct datosInstanciaCWP,struct datosSolucionCWP> {

public:
	CWP();
	virtual ~CWP();
	int leerInstancia(char * archivo);
	float evaluarSolucion(struct datosSolucionCWP* sol);
	struct datosSolucionCWP * generarSolucionRandom();
	void imprimirSolucion(struct datosSolucionCWP * sol);
	void imprimirInstancia();
	void liberarMemoriaSolucion(struct datosSolucionCWP *sol);
private:
	int reservarMemoriaInstancia();
	void liberarMemoriaInstancia();
};

}

#endif /* TSP_H_ */
