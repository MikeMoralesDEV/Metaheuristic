#include "CPH.h"

#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <float.h>
#include <time.h>
#include <math.h>

using namespace std;


namespace mh {

CPH::CPH() {
	data.p=0;
	data.n=0;
	data.c=0;
}

CPH::~CPH() {
	liberarMemoriaInstancia();
}

int CPH::reservarMemoriaInstancia() {


	data.d=new double *[(data.n)+1];
	for(int i=0;i<data.n+1;i++){
		data.d[i]=new double[(data.n)+1];
	}


	data.no=new nodo[data.n];

	return 0;
}

void CPH::liberarMemoriaInstancia() {

	for(int i=0;i<data.n+1;i++){
		delete [] data.d[i];
	}

	delete [] data.d;

}

void CPH::liberarMemoriaSolucion(struct datosSolucionCPH *sol){

		delete [] sol->x;
		delete sol;

}

int CPH::leerInstancia(char * archivo) {

		ifstream fichero;
		fichero.open(archivo);
		int n,c,p,x,y,id,m;


		fichero>>n;
		fichero>>p;
		fichero>>c;

		data.n=n;
        data.p=p;
        data.c=c;

		reservarMemoriaInstancia();

		for(int i=0;i<data.n+1;i++){
            for(int j=0;j<data.n+1;j++){
                data.d[i][j]=0;

            }
		}

        while(!fichero.eof()){
            fichero>>id;
            fichero>>x;
            fichero>>y;
            fichero>>m;

            data.no[id-1].id=id;
            data.no[id-1].x=x;
            data.no[id-1].y=y;
            data.no[id-1].m=m;
		}


		for(int i=0;i<data.n+1;i++){
            for(int j=i+1;j<data.n+1;j++){
                if(i!=j){
                        data.d[i][j]=sqrt(pow(data.no[i].x - data.no[j].x,2) + pow(data.no[i].y - data.no[j].y,2));
                        data.d[j][i]=data.d[i][j];
                }

            }

		}

		fichero.close();
		return 1;



}


float CPH::evaluarSolucion(struct datosSolucionCPH *sol) {

	float sum=0.0;
	int j;
    for(int i=0;i<data.n;i++){
    	j=sol->x[i];
        sum=sum+data.d[i][j];
    }
		return sum;
}





struct datosSolucionCPH * CPH::generarSolucionRandom() {

	struct datosSolucionCPH * sol;
	sol= new struct datosSolucionCPH;
	sol->x=new int[data.n];

	int * v1=new int [data.n];
	int * v3=new int [data.p];
	bool * v2= new bool [data.n];

    for(int i=0;i<data.n;i++)v2[i]=false;
	for(int i=0;i<data.n;i++)sol->x[i]=i;

    int s=0;

	for(int i=0;i<data.n;i++){
		v1[i]=i;
	}

	for(int i=0;i<data.p;i++){
		s=rand()%((data.n)-1);
		v3[i]=v1[s];
		v1[s]=v1[data.n-i-1];
	}


	delete [] v2;




	int capacited [data.p];
    for(int i=0;i<data.p;i++)capacited[i]=data.c;

    bool concentrador=false,encuentra=false;


	for(int i=0;i<data.n;i++){
        for(int j=0;j<data.p;j++){
            			if (i==v1[j]){
            				sol->x[i]=j+data.p;
            				encuentra=true;
            			}

        }
        if(!encuentra){
                    while(!concentrador){
                          s=rand()%data.p;
                          if(capacited[s]-data.no[i].m<0){concentrador=false;}
                          else{
                                concentrador=true;
                                capacited[s]-=data.no[i].m;
                                sol->x[i]=s;
                               }
                            }

            			}
        else{

            encuentra=false;
        }
        concentrador=false;

        }


	delete [] v1;
	return sol;
}

void CPH::imprimirSolucion(struct datosSolucionCPH *sol) {
	cout<<"***************************"<<endl;
	cout<<"Concentradores:"<<endl;
	for(int i=0;i<data.n;i++)
    {
        cout<<sol->x[i]<<" ";
    }
	cout<<endl;
	cout<<"***************************"<<endl;

}

void CPH::imprimirInstancia() {
	cout<<"===================================================================="<<endl;
	cout<<"Dimensiones: "<<endl;
	cout<<"n="<<data.n << " p=" << data.p<< " c=" << data.c << endl;
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
