#include "TSP.h"
#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <float.h>
#include <time.h>

using namespace std;


namespace mh {


TSP::TSP() {

	data.m=0;
}

TSP::~TSP() {
	liberarMemoriaInstancia();
}

int TSP::reservarMemoriaInstancia() {
	data.d=new float *[data.m];
	for(int i=0;i<data.m;i++){
		data.d[i]=new float [data.m];
	}
	return 0;
}

void TSP::liberarMemoriaInstancia() {
	for(int i=0;i<data.m;i++){
		delete [] data.d[i];
	}
	delete [] data.d;
}

void TSP::liberarMemoriaSolucion(struct datosSolucionTSP *sol){
		delete [] sol->x;
		delete sol;
}

int TSP::leerInstancia(char * archivo) {
		ifstream fichero(archivo);
		int m;
		float r;
		fichero>>m;
        data.m=m;
		reservarMemoriaInstancia();
		for(int i=0;i<data.m;i++){
                for(int j=0;j<data.m;j++){
                    fichero>>r;
                    data.d[i][j]=r;
                }
		}
		fichero.close();
		return 1;
}



float TSP::evaluarSolucion(struct datosSolucionTSP *sol) {

        float min=0;

		for(int i=0;i<data.m-1;i++){
			min=min+data.d[sol->x[i]][(sol->x[i+1]%(data.m-1))];
		}
		return min;
	}

struct datosSolucionTSP * TSP::generarSolucionRandom() {

	struct datosSolucionTSP * sol;
	sol= new struct datosSolucionTSP;
	sol->x=new int[data.m];

	bool * v2= new bool [data.m];


    for(int i=0;i<data.m;i++)v2[i]=false;
	for(int i=0;i<data.m;i++)sol->x[i]=i;

    int s=0;
    int temp=0;


	for(int i=0;i<data.m;i++)
	{
	    for(int j=0;j<data.m;j++){

		s=rand()%(data.m-1);
	    temp=sol->x[i];
	    sol->x[i]=sol->x[s];
	    sol->x[s]=temp;}
	}
	delete [] v2;
	return sol;
}


void TSP::imprimirSolucion(struct datosSolucionTSP *sol) {
	cout<<"***************************"<<endl;
	cout<<"Elementos escogidos:"<<endl;
	for(int i=0;i<data.m;i++)
    {
        cout<<sol->x[i]<<" ";
    }
	cout<<endl;
	cout<<"***************************"<<endl;

}

void TSP::imprimirInstancia() {
	cout<<"===================================================================="<<endl;
	cout<<"Dimensiones: "<<endl;
	cout<<"m="<<data.m << endl;
	cout<<"d de conectividad: "<<endl;
	for( int i=0;i<data.m;i++){
		for( int j=0;j<data.m;j++){
			cout<<data.d[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<"===================================================================="<<endl;

}

}
