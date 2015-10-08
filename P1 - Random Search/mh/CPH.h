#ifndef CPH_H_
#include <iostream>
#define CPH_H_

#include "Problema.h"

namespace mh {

struct nodo {
	int id;
	int x;
	int y;
	int m;


};

struct datosInstanciaCPH{
	int p;//Hubs
	int n;
	int c;
	double ** d;
	struct nodo * no;
};

struct datosSolucionCPH{
	int * x;
};




class CPH: public mh::Problema<struct datosInstanciaCPH,struct datosSolucionCPH> {

public:
	CPH();
	virtual ~CPH();
	int leerInstancia(char * archivo);
	float evaluarSolucion(struct datosSolucionCPH* sol);
	struct datosSolucionCPH * generarSolucionRandom();
	void imprimirSolucion(struct datosSolucionCPH * sol);
	void imprimirInstancia();
	void liberarMemoriaSolucion(struct datosSolucionCPH *sol);
private:
	int reservarMemoriaInstancia();
	void liberarMemoriaInstancia();
};

}

#endif /* TSP_H_ */
