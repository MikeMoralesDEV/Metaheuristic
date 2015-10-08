



#include "TSP.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <stdlib.h>
#include <float.h>
#include <time.h>
#include <algorithm>
#include <math.h>
// Incluir los namespaces que vayais a utilizar
using namespace std;


namespace clases {


TSP::TSP() {

	data.m=0;
}

TSP::~TSP() {
	liberarMemoria();
}

int TSP::tamano(){

	return data.m;

}

int TSP::reservarMemoria() {
	data.matriz=new float *[data.m];
	for(int i=0;i<data.m;i++){
		data.matriz[i]=new float [data.m];
	}
	return 0;
}

void TSP::liberarMemoria() {
	for(int i=0;i<data.m;i++){
		delete [] data.matriz[i];
	}
	delete [] data.matriz;
}

void TSP::liberarMemoriaSolucion(struct datosSolucionTSP *sol){
		delete [] sol->soluciones;
		delete sol;
}

int TSP::leerInstancia(char * archivo) {
		ifstream fichero(archivo);
		int m;
		float r;
		fichero>>m;
        data.m=m;
		reservarMemoria();
		for(int i=0;i<data.m;i++){
                for(int j=0;j<data.m;j++){
                    fichero>>r;
                    data.matriz[i][j]=r;
                }
		}
		fichero.close();
		return 0;
}



float TSP::evaluarSolucion(struct datosSolucionTSP *sol) {

        float min=0;

		for(int i=0;i<data.m-1;i++){
			min=min+data.matriz[sol->soluciones[i]][(sol->soluciones[i+1]%(data.m-1))];
		}
		return min;
	}


float TSP::evaluarSolucion2(struct datosSolucionTSP *sol,int valor,int w,int p) {

        float final=valor;


		for(int i=0;i<data.m-1;i++){
                if(i==(w-1)){
                    final=final-data.matriz[sol->soluciones[i]][(sol->soluciones[i+1]%(data.m-1))];
                    final=final+data.matriz[sol->soluciones[i]][(sol->soluciones[p]%(data.m-1))];
                }
                else{
                        if(i==w){

                    final=final-data.matriz[sol->soluciones[i]][(sol->soluciones[i+1]%(data.m-1))];
                    final=final+data.matriz[sol->soluciones[p]][(sol->soluciones[i+1]%(data.m-1))];

                        }

                }
                if(i==(p-1)){
                    final=final-data.matriz[sol->soluciones[i]][(sol->soluciones[i+1]%(data.m-1))];
                    final=final+data.matriz[sol->soluciones[i]][(sol->soluciones[w]%(data.m-1))];
                }
                else{
                        if(i==p){

                    final=final-data.matriz[sol->soluciones[i]][(sol->soluciones[i+1]%(data.m-1))];
                    final=final+data.matriz[sol->soluciones[w]][(sol->soluciones[i+1]%(data.m-1))];

                        }

                }

		}
		return final;
	}

struct datosSolucionTSP * TSP::generarSolucionRandom() {


	struct datosSolucionTSP * sol;
	sol= new struct datosSolucionTSP;
	sol->soluciones=new int[data.m];

	bool * v2= new bool [data.m];


    for(int i=0;i<data.m;i++)v2[i]=false;
	for(int i=0;i<data.m;i++)sol->soluciones[i]=i;

    int s=0;
    int temp=0;


	for(int i=0;i<data.m;i++)
	{
	    for(int j=0;j<data.m;j++){

		s=rand()%(data.m-1);
	    temp=sol->soluciones[i];
	    sol->soluciones[i]=sol->soluciones[s];
	    sol->soluciones[s]=temp;}
	}
	delete [] v2;
	return sol;
}


void TSP::imprimirSolucion(struct datosSolucionTSP *sol) {
	cout<<"***************************"<<endl;
	cout<<"Elementos escogidos:"<<endl;
	for(int i=0;i<data.m;i++)
    {
        cout<<sol->soluciones[i]<<" ";
    }
	cout<<endl;
	cout<<"***************************"<<endl;

}

void TSP::imprimirInstancia() {
	cout<<"===================================================================="<<endl;
	cout<<"Dimensiones: "<<endl;
	cout<<"m="<<data.m << endl;
	cout<<"Matriz de conectividad: "<<endl;
	for( int i=0;i<data.m;i++){
		for( int j=0;j<data.m;j++){
			cout<<data.matriz[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<"===================================================================="<<endl;

}



struct datosSolucionTSP * TSP::generarVecindario(datosSolucionTSP * sol, int vecino, int j) {

    int aux=0;
    //data.m //son los elegidos
    struct datosSolucionTSP * sol2;
	sol2= new struct datosSolucionTSP;
	sol2->soluciones=new int[data.m];
	sol2=sol;
	float beta=data.m/2;
	vector <float>  aristas,aristas2;




	for(int i=0;i<data.m-1;i++){
              aristas2.push_back(data.matriz[sol->soluciones[i]][sol->soluciones[i+1]]);
	}
    std::sort(aristas2.begin(),aristas2.end());

for(int i=0;i<data.m;i++){
              aristas.push_back(aristas2[data.m-i]);
	}

    for(int i=0;i<data.m-1;i++){
        if((data.matriz[sol->soluciones[i]][sol->soluciones[i+1]])==aristas[vecino]){
                    aux=sol->soluciones[i+1];
                    sol->soluciones[i+1]=sol->soluciones[j];
                    sol->soluciones[j]=aux;
                    i=data.m;
        }
    }




    return sol;

}



struct datosSolucionTSP * TSP::aplicarBusquedaLocal(struct datosSolucionTSP *sol, bool firstImprovement){

    struct datosSolucionTSP * sol2;
	sol2= new struct datosSolucionTSP;
	sol2->soluciones=new int[data.m];
    struct datosSolucionTSP * solnueva;
	solnueva= new struct datosSolucionTSP;
	solnueva->soluciones=new int[data.m];
	bool condicionParada=false,cond2=true;
	bool * seleccionados=new bool[data.m];
    for(int i=0;i<data.m;i++)seleccionados[i]=false;
	int j=0,i=0,w=0,bucle=0,bucle2=-1;
    sol2=sol;
    float beta=0.5;

 float valorObtenido = evaluarSolucion(sol2);
 float valorObtenido2;

	while(!condicionParada){


        if(firstImprovement){
                while(cond2){
                    if(bucle<50)
                    	w=rand()%data.m;

                    if(!seleccionados[w]){
                    	//Asi evitamos el propio y loscolindantes
                    if((w!=i) | (w!=i-1) | (w!=i+1)){cond2=false;}
                    else{
                        w=w+3;
                        w=w%data.m;
                        cond2=false;
                    }
                }
                else{

                    bucle++;

                }
                if(bucle>50){
                w=bucle2;
                w=w%data.m;
                bucle2++;
                }
                }
        }
        else{


            w=w%data.m;

        }
        if(w==data.m){w=0;condicionParada=true;}

        solnueva=generarVecindario(sol,i,w);

        valorObtenido2 = evaluarSolucion(solnueva);

        if(valorObtenido2<valorObtenido){
            sol2=solnueva;

            valorObtenido=valorObtenido2;

            if(firstImprovement)condicionParada=true;

            }

        j++;
         if(j>(data.m*beta))condicionParada=true;
         i++;

         w++;
         }

return sol2;


    }
	struct datosSolucionTSP * TSP::aplicarEnfriamientoSimulado(struct datosSolucionTSP *sol, float tFinal, float alpha){

  struct datosSolucionTSP * sol2;
	sol2= new struct datosSolucionTSP;
	sol2->soluciones=new int[data.m];
    struct datosSolucionTSP * solnueva;
	solnueva= new struct datosSolucionTSP;
	solnueva->soluciones=new int[data.m];
    sol2=sol;
    struct datosSolucionTSP * sol3;
	sol3= new struct datosSolucionTSP;
	sol3->soluciones=new int[data.m];

    float solucion1=0;
    float solucion2=0;
    float decrecim=0;
    float T=0;
    int i=0,j=0,x=0,w=0;

    bool cond1,cond2;
    cond1=cond2=false;


    while(!cond1){

        sol3=sol2;
    while(!cond2){

               x=0;


                w=rand()%data.m;

                    if((w!=i) | (w!=i-1) | (w!=i+1))cond2=false;
                    else{
                        w=w+3;
                        w=w%data.m;
                        cond2=false;
                    }




                solnueva=generarVecindario(sol,i,w);
                solucion1=evaluarSolucion(solnueva);
                solucion2=evaluarSolucion2(sol2,solucion1,i,w);
                decrecim=solucion1-solucion2;






                if((decrecim<0) | ((rand() / (double)RAND_MAX)<=exp(-decrecim/T))){


                                sol2=solnueva;


                }
                if(solucion1<solucion2){
                                sol2=solnueva;


                        }
            if(x>data.m){cond2=true;}
            if(j>0.1*data.m){cond2=true;}


                i++;
                x++;
                j++;
                solnueva=sol;

    }

        T=T*alpha;
        if(i>1000*data.m)cond1=true;
        if(sol2==sol3)cond1=true;
        if((tFinal<T))cond1=true;



}




    return sol2;
}





}
