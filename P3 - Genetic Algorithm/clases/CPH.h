#ifndef CPH_H_
#define CPH_H_

#include <iostream>
#include "Problema.h" 
#include "AlgoritmoGenetico.h"

using namespace std;

namespace mh {

struct datosInstanciaCPH{
	// Decidir que tiene!
	int n;
	int c;
	int p;
	float **distancia;
	//int *posicion;
	struct datosNodosCPH *nodos;
	int *demandaV;
};

struct datosSolucionCPH{
	// Decidir que tiene!
	int *VectorSolucion;
	int *posicion;
	float aptitud;

};

struct datosNodosCPH{
	int x;
	int y;
	int demanda;

};

class CPH: public mh::Problema<struct datosInstanciaCPH,struct datosSolucionCPH>
			{

public:
	CPH();
	virtual ~CPH();
	int leerInstancia(char *archivo);//int para devolver un error
	float evaluarSolucion(struct datosSolucionCPH* sol);//doble bucle y cuando ambos son T mirar cual es la minima distancia.
	struct datosSolucionCPH * generarSolucionRandom();//general n valores aleatorios que son los que van a ser T
	void imprimirSolucion(struct datosSolucionCPH * sol);
	void imprimirInstancia();//imprimir la matriz de distancia n y m
	void liberarMemoriaSolucion(struct datosSolucionCPH *sol);//liberar una solucion
	struct datosSolucionCPH * aplicarAlgoritmoGenetico(int tamanoPoblacion, float pCruce, float pMutacion, int nEval, bool estacionario, string archivo);
	void operadorMutacion(datosSolucionCPH *ind);
	void operadorCruce(datosSolucionCPH *ind1,datosSolucionCPH *ind2);
	struct datosSolucionCPH ** seleccionPorTorneo(datosSolucionCPH **pob, int tamanoTorneo, int tamanoPoblacion, int numeroSeleccion);
	struct datosSolucionCPH ** seleccionPorRuleta(datosSolucionCPH **pob, int tamanoPoblacion, int numeroSeleccion);
	struct datosSolucionCPH * mejorSolucionPoblacion(datosSolucionCPH **pob, int tamanoPoblacion);


private:
	int reservarMemoria();
	void liberarMemoria();
	struct datosSolucionCPH * reservaMemoriaSolucion();

};

}

#endif /* CPH_H_ */
