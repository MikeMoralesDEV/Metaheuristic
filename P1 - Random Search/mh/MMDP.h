/*
 * MMDP.h
 *
 *  Created on: 06/02/2013
 *      Author: pedroa
 */

#ifndef MMDP_H_
#define MMDP_H_

#include "Problema.h"
#include <vector>

using namespace std;

namespace mh {

struct datosInstanciaMMDP{
	int n;
	int m;
	float** d;
};

struct datosSolucionMMDP{
	bool * x;
};

class MMDP: public mh::Problema<struct datosInstanciaMMDP,struct datosSolucionMMDP> {

public:
	MMDP();
	virtual ~MMDP();
	int leerInstancia(char *archivo);
	float evaluarSolucion(struct datosSolucionMMDP* sol);
	struct datosSolucionMMDP * generarSolucionRandom();
	void imprimirSolucion(struct datosSolucionMMDP * sol);
	void imprimirInstancia();
	void liberarMemoriaSolucion(struct datosSolucionMMDP *sol);
private:
	int reservarMemoriaInstancia();
	void liberarMemoriaInstancia();
};

}

#endif /* MMDP_H_ */
