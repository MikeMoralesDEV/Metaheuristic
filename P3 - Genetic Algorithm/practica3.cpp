#include <iostream>
#include <unistd.h>
#include <cstring>
#include <time.h>
#include <stdlib.h>
#include <cstdlib>
#include <sstream>
#include <string>

#include "clases/CPH.h" //Incluye Problema.h y AlgoritmoGenetico.h
#include <math.h>
#include <cmath>

using namespace std;
using namespace mh;

template <class PROBLEMA,typename datosSolucion>
int procesarDatos(char *nombre, char *tipo, char *modo, string fichero) {
	int error=EXIT_SUCCESS;
	mejora=NULL;
	PROBLEMA *p = new PROBLEMA();
	if((error=p->leerInstancia(nombre))!=1){
		cout << "Error al leer la instancia del problema" << endl;
		return error;
	}
	datosSolucion *mejora=new datosSolucion;

	if (strcmp(tipo,"AGg") == 0)
	{
	mejora=p->aplicarAlgoritmoGenetico(200, 0.9, 0.15, 500, false, fichero);
	}
	else if (strcmp(tipo,"AGe") == 0)
	{
	mejora=p->aplicarAlgoritmoGenetico(200, 0.9, 0.15, 50, true, fichero);
	}


	p->imprimirSolucion(mejora);
	float imprimir=p->evaluarSolucion(mejora);
	cout<<"Función objetivo final: "<<imprimir<<endl;
	p->liberarMemoriaSolucion(mejora);

	delete p;
	return error;
}


int main(int argc, char **argv) {

	// Procesamiento de la línea de comandos
	bool pflag,sflag,fflag, aflag;
	char *pvalue, *fvalue, *avalue;
	int semilla;
	string nombre;
	int opcion;
	while ((opcion = getopt (argc, argv, "f:s:p:a:")) != -1)
	{
		switch (opcion)
		{

			case 'f':
				fvalue=optarg;
				fflag=true;
			break;

			case 's':
			  semilla=atoi (optarg);
			  sflag=true;
			break;
			case 'p':
				pvalue=optarg;
				pflag=true;
			break;
			case 'a':
				avalue=optarg;
				aflag=true;
			break;
		}
	}
	//Control de errores
	if(!fflag){
		cout<< "Es necesario especificar el nombre del fichero a procesar" << endl;
		return -1;
	}

	if(sflag){
		srand(semilla);
	}
	else{

		srand(time(NULL));
	}

	if(pflag && strcmp(pvalue,"CPH") == 0){
		cout<< "Problema CPH. Instancia " << fvalue << "..."<< endl;
		if (aflag)
		{
					//Preparacion del archivo y la semilla para procesar la instancia. Uso el archivo para ir registrando el elite de algoritmo genetico.
					string cojosemilla;
					ostringstream aux;
					aux << semilla;
					cojosemilla = aux.str();
					nombre.erase(0,18); //Limpio bufer


					nombre ="prueba.txt";
					cout << nombre << endl;
			if(procesarDatos<CPH,struct datosSolucionCPH>(fvalue, avalue,pvalue, nombre) != 1)
				return EXIT_FAILURE;
		}

	}

	return EXIT_SUCCESS;
}

