/*
 * MMDP.h
 *
 *  Created on: 21/02/2014
 *      Author: pedroa
 */

#ifndef MMDP_H_
#include <iostream>
#define MMDP_H_


#include "Problema.h"

namespace clases {

struct datosInstanciaMMDP{
	// Decidir que tiene!
	int n;
	int m;
	float ** matriz;
};

struct datosSolucionMMDP{
	// Decidir que tiene!
	int * soluciones;
};

class MMDP: public clases::Problema<struct datosInstanciaMMDP,struct datosSolucionMMDP> {

public:
	MMDP();
	virtual ~MMDP();
	int leerInstancia(char * archivo);
	int tamano();
	float evaluarSolucion(struct datosSolucionMMDP* sol);
	struct datosSolucionMMDP * generarSolucionRandom();
	void imprimirSolucion(struct datosSolucionMMDP * sol);
	void imprimirInstancia();
	void liberarMemoriaSolucion(struct datosSolucionMMDP *sol);
	struct datosSolucionMMDP * generarVecindario(datosSolucionMMDP * sol, int vecino);
	struct datosSolucionMMDP * generarVecino(struct datosSolucionMMDP *sol, int i, int j);
	struct datosSolucionMMDP * aplicarBusquedaLocal(struct datosSolucionMMDP *sol, bool firstImprovement);
	struct datosSolucionMMDP * aplicarEnfriamientoSimulado(struct datosSolucionMMDP *sol, float tFinal, float alpha);
private:
	int reservarMemoria();
	void liberarMemoria();
};

}

#endif /* MMDP_H_ */
