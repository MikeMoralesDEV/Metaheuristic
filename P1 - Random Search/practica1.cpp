//============================================================================
// Name        : practica1.cpp
// Author      : Miguel Morales Carmona	
// Version     : 1.0
// Copyright   : Universidad de Córdoba
// Description : Primera práctica asignatura Metaheurísticas
//============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <ctime>    // Para cojer la hora time()
#include <cstdlib>  // Para establecer la semilla srand() y generar números aleatorios rand()
#include <string.h>
#include <vector>
#include "mh/MMDP.h"
#include "mh/CWP.h"
#include "mh/CPH.h"
#include "mh/TSP.h"
#include "mh/Problema.h"

using namespace mh;
using namespace std;

template <class PROBLEMA,typename datosSolucion>
int procesarDatos(char *nombre) {
	int error=EXIT_SUCCESS;
	PROBLEMA p = PROBLEMA();
	if((error=p.leerInstancia(nombre))!=1){
		cout << "Error al leer la instancia del problema" << endl;
		return error;
	}
	p.imprimirInstancia();
	float maximo = 0;
	float minimo = 0;
	for(int i=0; i<1000; i++){
		datosSolucion *x = p.generarSolucionRandom();
		cout << "Solución generada (iteracion " << i << "): " << endl;
		p.imprimirSolucion(x);
		float valorObtenido = p.evaluarSolucion(x);
		if(i==0){
			maximo = minimo = valorObtenido;
		}
		else{
			if(valorObtenido>maximo)
				maximo = valorObtenido;
			if(valorObtenido<minimo)
				minimo = valorObtenido;
		}
		cout << "Función objetivo: " << valorObtenido << endl;
		p.liberarMemoriaSolucion(x);
	}
	cout << endl << endl << "==> Valores extremos generados: máximo=" << maximo << " mínimo=" << minimo << endl;

	return error;
}

struct CLIParams
{
  CLIParams ()
    : pflag(0), //Valores por defecto de los argumentos opcionales.
      sflag(0.0),
      fichero(""),
      seed(0),
      tipo("")
    {}
  int seed;
  char * tipo;
  char * fichero;
  int pflag;
  int sflag;
};

static int
parseCLI (int argc, char* const* argv, CLIParams& params) throw ()
{
  // Esta es una forma habitual de recoger argumentos con getopt
  // se usa una iteracion y cada elemento se pasa por un switch-case
  int opcion;
  string nombre;
  while ((opcion = getopt (argc, argv, "p:f:s:")) != -1)
  {

    switch (opcion)
    {

    case 'f':
	params.fichero = optarg;
	break;

    case 'p':
	params.pflag=1;
	params.tipo = optarg;
	break;

    case 's':
    params.sflag=1;
	params.seed = atoi (optarg);
	break;

      case '?': // en caso de error getopt devuelve el caracter ?

	if (isprint (optopt))
	  std::cerr << "Error: Opción desconocida \'" << optopt
	    << "\'" << std::endl;
	else
	  std::cerr << "Error: Caracter de opcion desconocido \'x" << std::hex << optopt
	    << "\'" << std::endl;
	exit (EXIT_FAILURE);

	// en cualquier otro caso lo consideramos error grave y salimos
      default:
	std::cerr << "Error: línea de comandos errónea." << std::endl;
	exit(EXIT_FAILURE);
    }  // case

  }// while


  if( params.fichero == ""){

  	cout << "El parametro -f es obligatorio" << endl;
  	exit(-1);

  }
    return optind;
}

int main(int argc, char **argv) {

	// Procesar línea de comandos...
	    CLIParams params;

	    int argObligados = parseCLI(argc, argv, params);

	    std::cout << "Los parámetros opcioneales son:" << std::endl;
	    std::cout << "-f\t" << params.fichero << std::endl;
	    std::cout << "-s\t" << params.seed << std::endl;
	    std::cout << "-p\t" << '\"' << params.tipo << '\"' << std::endl;

	    std::cout << "Hay " << argc-argObligados << " parámetros obligados que son: " << std::endl;

	    for (int i = argObligados; i<argc; ++i)
	      std::cout << '\"' << argv[i] << '\"' << std::endl;
	// Semilla de los números aleatorios especificado por un argumento
	if(params.sflag){
		srand(params.seed);
	}
	// Semilla no especificada, usar la hora
	else{
		srand(time(NULL));
	}

	// Tipo de problema
	if(params.pflag && strcmp(params.tipo,"MMDP") == 0){
		cout<< "Problema MMDP. Instancia " << params.fichero << "..."<< endl;
		if(procesarDatos<MMDP,struct datosSolucionMMDP>(params.fichero) != 1)
			return EXIT_FAILURE;
	}else if(params.pflag && strcmp(params.tipo,"TSP") == 0){
		cout<< "Problema TSP. Instancia " << params.fichero << "..."<< endl;
		if(procesarDatos<TSP,struct datosSolucionTSP>(params.fichero) != 1)
			return EXIT_FAILURE;
	}else if(params.pflag && strcmp(params.tipo,"CWP") == 0){
		cout<< "Problema CWP. Instancia " << params.fichero << "..."<< endl;
		if(procesarDatos<CWP,struct datosSolucionCWP>(params.fichero) != 1)
			return EXIT_FAILURE;
	}else if(params.pflag && strcmp(params.tipo,"CPH") == 0){
		cout<< "Problema CPH. Instancia " << params.fichero << "..."<< endl;
		if(procesarDatos<CPH,struct datosSolucionCPH>(params.fichero) != 1)
			return EXIT_FAILURE;
	}
	// ... resto de problemas
	// Por defecto, el MMDP
	else{
		cout<< "Problema MMDP. Instancia " << params.fichero << "..."<< endl;
		if(procesarDatos<MMDP,struct datosSolucionMMDP>(params.fichero) != 1)
			return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

