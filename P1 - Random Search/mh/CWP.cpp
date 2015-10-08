#include "CWP.h"
#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <float.h>
#include <time.h>
using namespace std;


namespace mh {

CWP::CWP() {
	data.m=0;
	data.n=0;
}

CWP::~CWP() {
	liberarMemoriaInstancia();
}

int CWP::reservarMemoriaInstancia() {


	data.d=new int*[(data.n)+1];


	for(int i=0;i<data.n+1;i++){
		data.d[i]=new int [(data.n)+1];
	}

	return 0;
}

void CWP::liberarMemoriaInstancia() {

	for(int i=0;i<data.n+1;i++){
		delete [] data.d[i];
	}

	delete [] data.d;

}

void CWP::liberarMemoriaSolucion(struct datosSolucionCWP *sol){

		delete [] sol->x;
		delete sol;

}

int CWP::leerInstancia(char * archivo) {

		ifstream fichero(archivo);
		int n, m, x,y;

		fichero>>n;
		fichero>>n;
		fichero>>m;

		data.n=n;
        data.m=m;

		reservarMemoriaInstancia();

		for(int i=0;i<data.n+1;i++){
            for(int j=0;j<data.n+1;j++){
                data.d[i][j]=0;

            }
		}

		for(int i=0;i<data.n+1;i++){

            fichero>>x;
            fichero>>y;

			data.d[x-1][y-1]=1;
			data.d[y-1][x-1]=1;

		}
		fichero.close();
		return 1;



}


float CWP::evaluarSolucion(struct datosSolucionCWP *sol) {

	int* aux = new int[data.n];
	int f,c;
	int aristas=0, max=0;

	for(int i = 0; i < data.n; i++)
	aux[i] = sol->x[i];


	for(int x = 1; x<data.n; x++){
		aristas=0;
		for(int i=0; i<x; i++){
				f=aux[i];
				for(int j=x; j<data.n; j++){

					c=aux[j];
					aristas=aristas+data.d[f][c];
					if(aristas>max){
						max=aristas;
					}
				}
		}
	}
	return max;
}


struct datosSolucionCWP * CWP::generarSolucionRandom() {

	struct datosSolucionCWP * sol;
	sol= new struct datosSolucionCWP;
	sol->x=new int[data.m];

	int * v1=new int [data.n];
	bool * v2= new bool [data.n];

    for(int i=0;i<data.n;i++)v2[i]=false;
	for(int i=0;i<data.n;i++)sol->x[i]=i;

    int s=0;

    for(int i=0;i<data.n;i++){
		v1[i]=i;
        }

	for(int i=0;i<data.n;i++){
		int s=rand()%(data.n-i);
		sol->x[i]=v1[s];
		v1[s]=v1[data.n-i-1];
        }

	delete [] v1;
	delete [] v2;

	return sol;
}

void CWP::imprimirSolucion(struct datosSolucionCWP *sol) {
	cout<<"***************************"<<endl;
	cout<<"Elementos escogidos:"<<endl;
	for(int i=0;i<data.n;i++)
    {
        cout<<sol->x[i]<<" ";
    }
	cout<<endl;
	cout<<"***************************"<<endl;

}

void CWP::imprimirInstancia() {
	cout<<"===================================================================="<<endl;
	cout<<"Dimensiones: "<<endl;
	cout<<"m="<<data.m << " n=" << data.n << endl;
	cout<<"d de conectividad: "<<endl;
	for( int i=0;i<data.n;i++){
		for( int j=0;j<data.n;j++){
			cout<<data.d[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<"===================================================================="<<endl;

}

}
