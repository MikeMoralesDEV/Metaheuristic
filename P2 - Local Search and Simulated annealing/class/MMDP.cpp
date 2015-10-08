/*
 * MMDP.cpp
 *
 *  Created on: 21/02/204
 *      Author: pedroa
 */




// INCLUDES NECESARIOS

#include "MMDP.h"
#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <float.h>
#include <time.h>
#include <math.h>
// Incluir los namespaces que vayais a utilizar
using namespace std;


namespace clases {

MMDP::MMDP() {
	//inicializar n y m
	data.m=0;
	data.n=0;
}

MMDP::~MMDP() {
	liberarMemoria();
}

int MMDP::reservarMemoria() {


	data.matriz=new float *[data.n];


	for(int i=0;i<data.n;i++){
		data.matriz[i]=new float [data.n];
	}

	return 0;
}

void MMDP::liberarMemoria() {

	//liberamos cada vector del vector inicial, es decir dejamos solo la fila 1
	for(int i=0;i<data.n;i++){
		delete [] data.matriz[i];
	}

	//eliminamos la fila 1 que quedaba
	delete [] data.matriz;

}

void MMDP::liberarMemoriaSolucion(struct datosSolucionMMDP *sol){

		//Borramos el vector apuntado por sol->
		delete [] sol->soluciones;

		//Borramos sol
		delete sol;

}

int MMDP::tamano(){

	return data.n;

}
int MMDP::leerInstancia(char * archivo) {

	fstream fichero;
	int n, m, x,y;
	float distancia;

	fichero.open(archivo);

	fichero>>n;
	data.n=n;

	fichero>>m;
	data.m=m;

	reservarMemoria();//nxn
	while(!fichero.eof()){

		fichero>>x;
		fichero>>y;
		fichero>>distancia;
		data.matriz[x][y]=distancia;
		data.matriz[y][x]=distancia;

	}
	fichero.close();
	return 0;


}


float MMDP::evaluarSolucion(struct datosSolucionMMDP *sol) {

	float min=99999999999999999999.9;

		for(int i=0;i<data.n-1;i++){

			for(int j=1;j<data.n;j++){

				if(sol->soluciones[i]==1 && sol->soluciones[j]==1 && i!=j)
				{
					if(data.matriz[i][j]<min){
						min=data.matriz[i][j];
					}
				}
			}
		}

		return min;
	}




struct datosSolucionMMDP * MMDP::generarSolucionRandom() {

	/*struct datosSolucionMMDP * sol;
	sol= new struct datosSolucionMMDP;
	sol->soluciones=new int[data.n];
	for(int i=0;i<data.n;i++)sol->soluciones[i]=0;
	int s=0;
	for(int i=0;i<data.m;i++)
	{
		s=rand()%data.n;
		if(sol->soluciones[s]==0)sol->soluciones[s]=1;
		else{
			i--;
		}
	}

	return sol;
*/

	struct datosSolucionMMDP * sol;
	sol= new struct datosSolucionMMDP;
	sol->soluciones=new int[data.n];

	for(int i=0; i<data.n; i++){

			sol->soluciones[i]=0;
		}

	//generacion de una solucion aleatoria
	int* numerosPorElegir = new int[data.n];
	for(int i = 0; i < data.n; i++)
		numerosPorElegir[i] = i;

	for(int i=0; i < data.m; i++)
	{
		int numeroElegido = rand() % (data.n-i);
		// Recordar el numero elegido
		sol->soluciones[numerosPorElegir[numeroElegido]]=1;
		// Ponemos en numeros por elegir, el ultimo que era valido, asi
		// son todos validos hasta data.n-i-1
		numerosPorElegir[numeroElegido]=numerosPorElegir[data.n-i-1];
	}
	delete [] numerosPorElegir;


	return sol;}

void MMDP::imprimirSolucion(struct datosSolucionMMDP *sol) {
	cout<<"***************************"<<endl;
	cout<<"Elementos escogidos:"<<endl;
	for(int i=0;i<data.n;i++)
    {
        cout<<sol->soluciones[i]<<" ";
    }
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
			cout<<data.matriz[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<"===================================================================="<<endl;

}

struct datosSolucionMMDP * MMDP::generarVecindario(datosSolucionMMDP * sol, int vecino) {

    int aux=0;
    //data.m //son los elegidos
    struct datosSolucionMMDP * sol2;
	sol2= new struct datosSolucionMMDP;
	sol2->soluciones=new int[data.n];
	sol2=sol;
    /*	bool encontrado = false;
	int j;

for(int i=0;i<data.n;i++){
        if(sol->soluciones[i]==1){
            while(!encontrado){
            	j=rand()%data.n;
                if(sol->soluciones[j]==0){
                	sol2->soluciones[j]=1;
                	sol2->soluciones[i]=0;

                	if(aux==vecino){
                    	encontrado=true;
                		i=data.n+10;
                	}
                	else{
                		sol2=sol;
                		//sol2=sol;
                	}
                	aux++;
                	encontrado=true;
                }

            };
        }
    }
*/
	int indice=rand()%(data.m-1);
			int contador=0;
	for(int i=0;i<data.n;i++){

		for(int j=i+1;j<data.n;j++){

			if(sol->soluciones[i]!=sol->soluciones[j]){
				contador++;
				if(contador==indice){
                	sol2->soluciones[j]=(sol2->soluciones[j]+1)%2;
                	sol2->soluciones[i]=(sol2->soluciones[i]+1)%2;
                	if(aux==vecino){
                	     		i=data.n+10;
                	     		j=data.n+10;
                	}
                	else{
                	   		sol2=sol;
                	                		//sol2=sol;
                	}
                	aux++;
				}
			}


		}

	}

    return sol2;

}



struct datosSolucionMMDP * MMDP::aplicarBusquedaLocal(struct datosSolucionMMDP *sol, bool firstImprovement){

    struct datosSolucionMMDP * sol2;
	sol2= new struct datosSolucionMMDP;
	sol2->soluciones=new int[data.n];
    struct datosSolucionMMDP * solnueva;
	solnueva= new struct datosSolucionMMDP;
	solnueva->soluciones=new int[data.n];
	bool condicionParada=false;
	int j=0,i=0;
    sol2=sol;


 float valorObtenido = evaluarSolucion(sol2);
 float valorObtenido2;
if(firstImprovement){
	while(!condicionParada){
        solnueva=generarVecindario(sol,i);

        valorObtenido2 = evaluarSolucion(solnueva);

        if(valorObtenido2<valorObtenido){
            sol2=solnueva;

            valorObtenido=valorObtenido2;

            condicionParada=true;

         }
        	j++;
        	if(j>5)condicionParada=true; //Optimo global o local
        i++;
         }
}else{

    sol2=generarVecindario(sol,i);


}
    //liberarMemoriaSolucion(solnueva);




return sol2;

}

struct datosSolucionMMDP * MMDP::generarVecino(struct datosSolucionMMDP *sol, int i, int j)
	{
		bool aux;

		aux = sol->soluciones[i];
		sol->soluciones[i] = sol->soluciones[j];
		sol->soluciones[j] = aux;

		return(sol);
	}

struct datosSolucionMMDP * MMDP::aplicarEnfriamientoSimulado(struct datosSolucionMMDP *sol, float tFinal, float alpha){


	int index[data.n];
		int vecino=0, mejora=0;
		int totaleval = 0;
		int SolucionesExploradas = 0;
		int solucionesAceptadas = 0;
		int solucionesCercanas = 0;
		struct datosSolucionMMDP * mejorSol= sol;
		struct datosSolucionMMDP * solNueva = sol;
		float funcionObjetivoInicial = evaluarSolucion(sol);
		float mejorSolucionEncontrada = funcionObjetivoInicial;
		float funcionObjetivo = funcionObjetivoInicial;
		float funcionObjetivoNueva;
		float tActual = (10*funcionObjetivo)/(-(log(0.3)));
		float probGenerar;


		//creamos un vextor de indices donde al principio estaran los indices de los 1 seguidos de los indices de los 0 del vector solucion.
		for(int i=0, x=0, y=data.n-1; i<data.n; i++){

				if(sol->soluciones[i]==1){

					index[x]=i;
					x++;
				}
				else{
					index[y]=i;
					y--;
				}
			}

		do{
			do{

				//Calculamos i y j para la obtencion de un vecino determinado
				int i=index[(vecino/(data.n-data.m))];
				int j=index[(vecino%(data.n-data.m))+data.m];
				vecino++;

				solNueva=generarVecino(sol, i, j);

				funcionObjetivoNueva = evaluarSolucion(solNueva);

				SolucionesExploradas++;
				totaleval++;

				//hay que maximizar la funcion objetivo
				if(funcionObjetivoNueva >= funcionObjetivo){

					if(funcionObjetivoNueva > mejorSolucionEncontrada){

						mejorSol = solNueva;
						mejorSolucionEncontrada = funcionObjetivoNueva;
					}

					sol=solNueva;
					funcionObjetivo=funcionObjetivoNueva;
					vecino=0;
					mejora=1;
					solucionesAceptadas++;

					int auxiliar=index[i];
					index[i]=index[j];
					index[j]=auxiliar;


					//colocamos la solucion intercambiada al final del vector de indices de la nueva solucion para que no vuelva a generarse que acabamos de cambiar
					auxiliar=index[i];
					index[i]=index[data.m-1];
					index[data.m-1]=auxiliar;

					auxiliar=index[j];
					index[j]=index[data.n-1];
					index[data.n-1]=auxiliar;

				}
				else{

					probGenerar = exp(-(((funcionObjetivo-funcionObjetivoNueva)/funcionObjetivoInicial)/tActual));

					float Aceptacion = (rand()%101);
					Aceptacion = Aceptacion/100;

					if(probGenerar > Aceptacion){

						sol = solNueva;
						funcionObjetivo=funcionObjetivoNueva;
						vecino=0;
						solucionesAceptadas++;

						int auxiliar=index[i];
						index[i]=index[j];
						index[j]=auxiliar;


						//colocamos la solucion intercambiada al final del vector de indices de la nueva solucion para que no vuelva a generarse que acabamos de cambiar
						auxiliar=index[i];
						index[i]=index[data.m-1];
						index[data.m-1]=auxiliar;

						auxiliar=index[j];
						index[j]=index[data.n-1];
						index[data.n-1]=auxiliar;
					}

				}


			}while(SolucionesExploradas < data.n && solucionesAceptadas < (0.1*data.n) && vecino < (data.m*(data.n-data.m)) && 50*data.n);

			tActual = tActual*alpha;
			solucionesAceptadas = 0;
			SolucionesExploradas = 0;
			mejora=0;



		}while( mejora==1 && tActual >= tFinal && totaleval < 50*data.n);




	return mejorSol;
	/*
    struct datosSolucionMMDP * sol2;
	sol2= new struct datosSolucionMMDP;
	sol2->soluciones=new int[data.n];
    struct datosSolucionMMDP * solnueva;
	solnueva= new struct datosSolucionMMDP;
	solnueva->soluciones=new int[data.n];
    sol2=sol;
    struct datosSolucionMMDP * sol3;
	sol3= new struct datosSolucionMMDP;
	sol3->soluciones=new int[data.n];

    float solucion1=0;
    float solucion2=0;
    float decrecim=0;
    float T=0;
    int i=0,j=0,x=0;
    imprimirSolucion(sol2);
    bool cond1,cond2;
    cond1=cond2=false;

while(!cond1){

        sol3=sol2;
    while(!cond2){

               x=0;


                //solnueva->soluciones=new int[data.n];
                solnueva=generarVecindario(sol,i);
               // solnueva=generarVecindario(sol,i);
                solucion1=evaluarSolucion(solnueva);
                solucion2=evaluarSolucion(sol2);
                decrecim=solucion1-solucion2;


                if((decrecim<0) | ((rand() / (double)RAND_MAX)<=exp(-decrecim/T))){


                                sol2=solnueva;
                                j++;


                }
                if(solucion1<solucion2){
                                sol2=solnueva;
                                j++;


                        }
            if(x>data.n){cond2=true;}
            if(j>0.1*data.n){cond2=true;}


                i++;
                x++;
                j++;
                solnueva=sol;

    }
        T=T*alpha;
        if(sol2==sol3)cond1=true;
        if((tFinal<T))cond1=true;
        if(i>50*data.n)cond1=true;
        if(solucionfinal>evaluarSolucion(sol2))
}



    return sol2;*/
}

}
