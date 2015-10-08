//============================================================================
// Name        : practica1.cpp
// Author      : Miguel Morales Carmona
// Version     : 1.0
// Copyright   : Universidad de C�rdoba
// Description : Pr�ctica 1 de Metaheur�sticas
//============================================================================

// Realizar los import necesarios
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include "class/MMDP.h"
#include "class/TSP.h"

// Incluir los namespaces que vayais a utilizar
using namespace std;
using namespace clases;


// Incluir los defines necesarios
char * pvalue = NULL;


// Funci�n de procesamiento. Es una plantilla, adem�s de los argumentos habituales
// recibe como argumento el tipo de la clase de problema a procesar, y el tipo de
// las soluciones correspondientes
float sacarmejor(char * nombre){

float valor=0;
string file,instancias="instancias/",N;
ifstream fichero("instancias/best_values_MMDP.txt");


bool cond=true;
N="MMDP/";
while(!fichero.eof()&&cond){
			//Asignamos x
			fichero>>file;
			//Asignamos y
			fichero>>valor;

			file=instancias+N+file;
            char * S = new char[file.length() + 1];
            strcpy(S,file.c_str());

			if(strcmp(S,nombre) == 0){

                cond=false;
			}
			else{
                valor=0;
			}

}

if(valor==0)
{
    N="TSP/";
    fichero.close();

    		fichero.open("instancias/best_values_TSP.txt");


    		while(!fichero.eof()&&cond){
			//Asignamos x
			fichero>>file;
			//Asignamos y
			fichero>>valor;

			file=instancias+N+file;
            char * S = new char[file.length() + 1];
            strcpy(S,file.c_str());

			if(strcmp(S,nombre) == 0){

                cond=false;
			}
			else{
                valor=0;
			}
}

}

fichero.close();
return valor;
}



template <class PROBLEMA,typename datosSolucion>
int procesarDatos(char *nombre,bool first) {
	int error=EXIT_SUCCESS;
	float valor=0;
	PROBLEMA *p = new PROBLEMA();
	if((error=p->leerInstancia(nombre))!=0){
		cout << "Error al leer la instancia del problema" << endl;
		return error;
	}
	cout << "La he leido" << endl;
	int n=p->tamano();

	if(!strcmp(pvalue,"MMDP")){
		n=n*50;
	}else{
		n=n*1000;
	}

	float maximo = 0;
	float minimo = 0;
        //srand(i);
        for(int j=0;j<n;j++){

            datosSolucion *x = p->generarSolucionRandom();

            float valorObtenido = p->evaluarSolucion(x);


            x=p->aplicarBusquedaLocal(x, first);

            valorObtenido = p->evaluarSolucion(x);

                p->imprimirSolucion(x);
		if(j==0){
			maximo = minimo = valorObtenido;
		}
		else{
			if(valorObtenido>maximo)
				maximo = valorObtenido;
			if(valorObtenido<minimo)
				minimo = valorObtenido;
		}

		p->liberarMemoriaSolucion(x);



	}
    valor=sacarmejor(nombre);

	if(!strcmp(pvalue,"MMDP")){
		cout << "Función objetivo final: " << maximo << endl;
	}else{
		cout << "Función objetivo final: " << minimo << endl;
	}

	delete p;
	return error;
}


template <class PROBLEMA,typename datosSolucion>
int procesarDatos2(char *nombre) {
	int error=EXIT_SUCCESS;
		float valor=0;
	PROBLEMA *p = new PROBLEMA();
	if((error=p->leerInstancia(nombre))!=0){
		cout << "Error al leer la instancia del problema" << endl;
		return error;
	}
	int n=p->tamano();

		if(!strcmp(pvalue,"MMDP")){
			n=n*50;
		}else{
			n=n*1000;
		}
	float maximo = 0;
	float minimo = 0;
	float tFinal=0.0001,alpha=0.8;
	for(int i=0;i<1000;i++){
        //srand(i);
            datosSolucion *x = p->generarSolucionRandom();
            float valorObtenido ;

            x=p->aplicarEnfriamientoSimulado(x, tFinal, alpha);
            valorObtenido = p->evaluarSolucion(x);

                p->imprimirSolucion(x);
		if(i==0){
			maximo = minimo = valorObtenido;
		}
		else{
			if(valorObtenido>maximo)
				maximo = valorObtenido;
			if(valorObtenido<minimo)
				minimo = valorObtenido;
		}


		p->liberarMemoriaSolucion(x);
	}
float elegido;

	if(!strcmp(pvalue,"MMDP")){
		elegido=maximo;
	}else{
		elegido=minimo;
	}
    valor=sacarmejor(nombre);
	valor=100*((elegido-valor)/valor);

	if(!strcmp(pvalue,"MMDP")){
		cout << "Función objetivo final: " << maximo << endl;
	}else{
		cout << "Función objetivo final: " << minimo << endl;
	}    delete p;
	return error;
}


int main(int argc, char **argv) {

	// Procesamiento de la l�nea de comandos

    int fflag = 0;
    int sflag = 0;
    int pflag = 0;
    char * fvalue = NULL;
    char * avalue = NULL;
    int svalue = 0;
    int c;

    /* Las variables optind,optarg y optopt las declara y actualiza
       impl�ticamente getopt()
    */


    /* ':' indica que 'c' tiene un argumento, si pusi�ramos '::' indicar�a
       que el argumento de 'c' es opcional */
    while ((c = getopt (argc, argv, "f:s:p:a:")) != -1)
    {

        switch (c)
        {
        case 'f':
            fflag = 1;
            fvalue=optarg;
            break;
        case 's':
            sflag = 1;
            svalue = atoi(optarg);
            break;
        case 'p':
        	pflag=1;
            pvalue = optarg;
            break;
        case 'a':
             avalue = optarg;
            break;
        case '?':
            if (optopt == 'c')
                fprintf (stderr, "Option -%c requires an argument.\n", optopt);
            else if (isprint (optopt))
                fprintf (stderr, "Unknown option `-%c'.\n", optopt);
            else
                fprintf (stderr,
                         "Unknown option character `\\x%x'.\n",
                         optopt);
            return 1;
        default:
            abort ();
            break;
        }
    }

	// Si no se ha especificado nombre de fichero
	if(!fflag){
		cout<< "Es necesario especificar el nombre del fichero a procesar" << endl;
		return -1;
	}

	// Establecer la semilla a lo que ha dicho el usuario
	if(sflag){
			srand(svalue);
	}
	// Establecer la semilla usando time(NULL)
	else{

			srand(time(NULL));
	}

	// Tipo de problema
	if(pflag && strcmp(avalue,"BLb") == 0 && strcmp(pvalue,"MMDP") == 0){

		if(procesarDatos<MMDP,struct datosSolucionMMDP>(fvalue,false) != 1)
			return EXIT_FAILURE;
	}
		if(pflag && strcmp(avalue,"BLf") == 0 && strcmp(pvalue,"MMDP") == 0){

		if(procesarDatos<MMDP,struct datosSolucionMMDP>(fvalue,true) != 1)
			return EXIT_FAILURE;
	}
        if(pflag && strcmp(avalue,"ES") == 0 && strcmp(pvalue,"MMDP") == 0){

		if(procesarDatos2<MMDP,struct datosSolucionMMDP>(fvalue) != 1)
			return EXIT_FAILURE;
	}
    if(pflag && strcmp(avalue,"BLf") == 0 && strcmp(pvalue,"TSP") == 0){

		if(procesarDatos<TSP,struct datosSolucionTSP>(fvalue,true) != 1)
			return EXIT_FAILURE;
	}
	   if(pflag && strcmp(avalue,"BLb") == 0 && strcmp(pvalue,"TSP") == 0){

		if(procesarDatos<TSP,struct datosSolucionTSP>(fvalue,false) != 1)
			return EXIT_FAILURE;
	}

        if(pflag && strcmp(avalue,"ES") == 0 && strcmp(pvalue,"TSP") == 0){

		if(procesarDatos2<TSP,struct datosSolucionTSP>(fvalue) != 1)
			return EXIT_FAILURE;
	}
	// Lo mismo para TSP, CWP y CPH (else if...)
	// Por defecto, el MMDP
	else{
		cout<< "Problema MMDP. Instancia " << fvalue << "..."<< endl;
		if(procesarDatos<MMDP,struct datosSolucionMMDP>(fvalue,true) != 1)
			return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

