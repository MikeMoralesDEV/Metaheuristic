/*
 * MMDP.cpp
 *
 *  Created on: 06/02/2013
 *      Author: pedroa
 */

#include "MMDP.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>  // Para establecer la semilla srand() y generar números aleatorios rand()
#include <limits>

using namespace std;

namespace mh {

MMDP::MMDP() {
	data.m=0;
	data.n=0;
}

MMDP::~MMDP() {
	liberarMemoriaInstancia();
}

int MMDP::reservarMemoriaInstancia() {
		data.d=new float *[data.n];

		for(int i=0;i<data.n;i++){
			data.d[i]=new float [data.n];
		}

		return 0;

}

void MMDP::liberarMemoriaInstancia() {
	for(int i=0;i<data.n;i++){
		delete [] data.d[i];
	}
	delete [] data.d;
}

void MMDP::liberarMemoriaSolucion(struct datosSolucionMMDP *sol){
	delete [] sol->x;

	delete sol;
}

int MMDP::leerInstancia(char *archivo) {
	fstream fichero;
	int n, m, x,y;
	float distancia;

	fichero.open(archivo);

	fichero>>n;
	data.n=n;

	fichero>>m;
	data.m=m;

	reservarMemoriaInstancia();//nxn
	while(!fichero.eof()){

		fichero>>x;
		fichero>>y;
		fichero>>distancia;
		data.d[x][y]=distancia;
		data.d[y][x]=distancia;

	}
	fichero.close();
	return 1;
}


float MMDP::evaluarSolucion(struct datosSolucionMMDP *sol) {

	float min=99999999999999999999.9;

		for(int i=0;i<data.n-1;i++){

			for(int j=1;j<data.n;j++){

				if(sol->x[i]==1 && sol->x[j]==1 && i!=j)
				{
					if(data.d[i][j]<min){
						min=data.d[i][j];
					}
				}
			}
		}
		return min;
}

struct datosSolucionMMDP * MMDP::generarSolucionRandom() {

	struct datosSolucionMMDP * sol;
	sol= new struct datosSolucionMMDP;
	sol->x=new bool[data.n];
	for(int i=0;i<data.n;i++)sol->x[i]=0;
	int s=0;

	for(int i=0;i<data.m;i++)
	{
		s=rand()%data.n;
		if(sol->x[s]==0)sol->x[s]=1;
		else{
			i--;
		}
	}

	return sol;
}

void MMDP::imprimirSolucion(struct datosSolucionMMDP *sol) {
	cout<<"***************************"<<endl;
	cout<<"Elementos escogidos:"<<endl;
	for(int i=0;i<data.n;i++)cout<<sol->x[i]<<" ";
	cout<<endl;
	cout<<"***************************"<<endl;

}

void MMDP::imprimirInstancia() {
	cout<<"===================================================================="<<endl;
	cout<<"Dimensiones: "<<endl;
	cout<<"m="<<data.m << " n=" << data.n << endl;
	cout<<"Matriz de conectividad: "<<endl;
	for( int i=0;i<data.n;i++){
		for( int j=0;j<data.n;j++){
			cout<<data.d[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<"===================================================================="<<endl;
}

}
