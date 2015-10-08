#include "CPH.h"

// INCLUDES NECESARIOS
#include <iostream>
#include <fstream>
#include <string.h> 
#include <stdlib.h>
#include <math.h>
#include <cstdlib>


using namespace std;
namespace mh {

CPH::CPH() {

	data.n=0;
	data.c=0;
	data.p=0;

}

CPH::~CPH() {
	liberarMemoria();

}

int CPH::reservarMemoria() {
	data.distancia =new float *[data.n];
	for (int i=0;i<data.n;i++)
	{
		data.distancia[i]= new float [data.n];

	}
	data.nodos=new struct datosNodosCPH [data.n];
	data.demandaV = new int [data.p];
	//data.posicion=new int [data.n];

	return 0;
}
struct datosSolucionCPH * CPH::reservaMemoriaSolucion(){
	struct datosSolucionCPH *sol=new struct datosSolucionCPH;
	sol->VectorSolucion = new int [data.n];
	sol->posicion = new int [data.p];

	return sol;
}
void CPH::liberarMemoria() {
	for (int i=0;i<data.n;i++)
	{
		delete [] data.distancia[i];
	}
	delete [] data.distancia;
	delete [] data.nodos;
	delete [] data.demandaV;

}

void CPH::liberarMemoriaSolucion(struct datosSolucionCPH *sol){

	delete [] sol->VectorSolucion;
	delete [] sol->posicion;

}

int CPH::leerInstancia(char *archivo) {

	ifstream fichero;
	fichero.open(archivo);


	char texto[128];
	char *linea;
	int res;

	//leer la primera linea
	fichero.getline(texto, 128);
	linea= strtok(texto, " ");
	data.n=atoi(linea);
	linea=strtok(NULL," ");
	data.p=atoi(linea);
	linea=strtok(NULL," ");
	data.c=atoi(linea);


	//llamar a reservar memoria
	res=reservarMemoria();
	int i=0, j=0,  nod=0, dis=0;
	//fichero.getline(texto, 128);

	while(!fichero.eof())
		{

			fichero >> nod >>i >>j>> dis;

			data.nodos[nod-1].x=i;

			data.nodos[nod-1].y=j;

			data.nodos[nod-1].demanda=dis;

			fichero.getline(texto, 128);
		}
	for(int i=0;i<data.n;i++)
	{
		for(int j=i+1;j<data.n;j++)
		{
			data.distancia[i][j]=sqrt(pow(data.nodos[i].x-data.nodos[j].x,2)+pow(data.nodos[i].y-data.nodos[j].y,2));
			data.distancia[j][i]=sqrt(pow(data.nodos[i].x-data.nodos[j].x,2)+pow(data.nodos[i].y-data.nodos[j].y,2));
		}
	}


	fichero.close();

	return 1;
}


float CPH::evaluarSolucion(struct datosSolucionCPH *sol) {

	int cliente=0;
	float solucion=0;

	for(int i=0;i<data.p;i++)
	 {
		 data.demandaV[i]=0;
	 }
	for(int k=0;k<data.p;k++)
	{
		for(int i=0;i<data.n;i++)
		{
			if((sol->VectorSolucion[i]==cliente || sol->VectorSolucion[i]==(data.p+cliente)) && data.demandaV[k]+data.nodos[i].demanda<data.c) //Controlo aqui tambien que no desborde, porque en el 100_10_10 me daba valores erróneos
			{
				data.demandaV[k]=data.demandaV[k]+data.nodos[i].demanda;
			}
		}
		cliente++;
	 }

	for(int p=0;p<data.p;p++) //por si se desborda en la demanda algun concentrador
	{
		if(data.demandaV[p]>data.c)
		{
			solucion=9999.99;
		}
	}
	if(solucion==0.0)
	{
		for(int i=0; i<data.n; i++)
		{
			if(sol->VectorSolucion[i] < data.p){
				int indiceConcentrador=0;
				for(int j=0; j< data.n; j++)
				{
					if(sol->VectorSolucion[j] == data.p + sol->VectorSolucion[i])
					{
						indiceConcentrador=j;
					}
				}
				solucion =solucion+data.distancia[i][indiceConcentrador];
			}
		}
	}
	return solucion;


/* ESte método para cuando controlo el no sobrepasar la capacidad en generar
	float sum=0.0;
	int j;
    for(int i=0;i<data.n;i++){
    	j=sol->VectorSolucion[i];
        sum=sum+data.distancia[i][j];
    }
		return sum;*/
}

struct datosSolucionCPH * CPH::generarSolucionRandom() { //Variante realizando permutaciones

	struct datosSolucionCPH * sol;
	sol= new struct datosSolucionCPH;
	sol->VectorSolucion=new int[data.n];

	int * v1=new int [data.n];
	int * v3=new int [data.p];
	bool * v2= new bool [data.n];

    for(int i=0;i<data.n;i++)v2[i]=false;
	for(int i=0;i<data.n;i++)sol->VectorSolucion[i]=i;

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
            				sol->VectorSolucion[i]=j+data.p;
            				encuentra=true;
            			}

        }
        if(!encuentra){
                    while(!concentrador){
                          s=rand()%data.p;
                          if(capacited[s]-data.nodos[i].demanda<0){concentrador=false;}
                          else{
                                concentrador=true;
                                capacited[s]-=data.nodos[i].demanda;
                                sol->VectorSolucion[i]=s;
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
	int i=0;
	cout<<"***************************"<<endl;
	cout<<"Elementos escogidos:"<<endl;
	for(i=0;i<data.n;i++)
	{
		cout<<" "<<sol->VectorSolucion[i];
	}
	cout<<endl;
	cout<<"***************************"<<endl;
}

void CPH::imprimirInstancia() {

	cout<<"Dimensiones :"<<endl;
	cout<<"p= "<<data.p;
	cout<<", n= "<<data.n;
	cout<<", c= "<<data.c<<endl;
	cout<<"Matriz de conectividad:"<<endl;

	for(int i=0;i<data.n;i++)
	{
		for(int j=0;j<data.n;j++)
		{
			cout<<" "<<data.distancia[i][j];
		}
		cout<<""<<endl;
	}
}
struct datosSolucionCPH * CPH::aplicarAlgoritmoGenetico(int tamanoPoblacion, float pCruce, float pMutacion, int nEval, bool estacionario, string archivo)
{

	struct datosSolucionCPH ** pob = new datosSolucionCPH * [tamanoPoblacion];
	struct datosSolucionCPH * mejor;
	mejor=reservaMemoriaSolucion();
	struct datosSolucionCPH ** pob2= new datosSolucionCPH * [(tamanoPoblacion)];
	struct datosSolucionCPH ** aux= new datosSolucionCPH * [(tamanoPoblacion+2)];
	float r=0.0;

	float NoMejora=0;
	int cont=0;

	for(int i=0; i<tamanoPoblacion; i++)
	{
		pob[i]=generarSolucionRandom();
		pob[i]->aptitud=evaluarSolucion(pob[i]);
		cont++;
	}
	ofstream flujoSalida;
	flujoSalida.open(archivo.c_str(), ios::out);
	for(int i=0; i<(tamanoPoblacion+2); i++)
				{
					aux[i]=reservaMemoriaSolucion();
				}
	if(estacionario) //AGe
	{
		cout<<"AGe"<<endl;
		do{

			struct datosSolucionCPH * auxmejor=mejorSolucionPoblacion(pob, tamanoPoblacion); //guardar elite para siguiente generacion

			for(int i=0;i<data.n;i++)
			{
				mejor->VectorSolucion[i]=auxmejor->VectorSolucion[i];
			}
			mejor->aptitud=auxmejor->aptitud;

			liberarMemoriaSolucion(auxmejor);

			pob2=seleccionPorRuleta(pob, tamanoPoblacion, 2);  //llamar funcion ruleta

			r = ((double)rand())/RAND_MAX;
			if (r<=pCruce)
			{
				operadorCruce(pob2[0],pob2[1]); //hacer cruce
			}

			for (int i=0;i<2;i++)
			{
				r = ((double)rand())/RAND_MAX;
				if(r<=pMutacion)
				{
					operadorMutacion(pob2[i]); //hacer mutacion
				}
			}

			for (int i=0;i<2; i++)//evaluar las que hayan sido cambiadas y se suma uno al contador por cada evalucion
			{
				if(pob2[i]->aptitud==-1)
				{
					pob2[i]->aptitud=evaluarSolucion(pob2[i]);
					cont++;
				}
			}

			//juntar las dos estructuras con un tamaño de tamañopoblacion+2

			for(int i=0;i<tamanoPoblacion;i++)
			{
				for(int j=0;j<data.n;j++)
				{

					aux[i]->VectorSolucion[j]=pob[i]->VectorSolucion[j];
				}

				aux[i]->aptitud=pob[i]->aptitud;
			}

			for(int i=0;i<data.n;i++)
			{
				aux[tamanoPoblacion]->VectorSolucion[i]=pob2[0]->VectorSolucion[i];
			}
			aux[tamanoPoblacion]->aptitud=pob2[0]->aptitud;

			for(int i=0;i<data.n;i++)
			{
				aux[tamanoPoblacion+1]->VectorSolucion[i]=pob2[1]->VectorSolucion[i];
			}
			aux[tamanoPoblacion+1]->aptitud=pob2[1]->aptitud;


			//--------Ya estan juntas las dos poblaciones en aux------//

			pob2=seleccionPorTorneo(aux,2,(tamanoPoblacion+2),tamanoPoblacion-1);//hacer torneo

			bool mejora=false;//ver si ha habido mejora
			for(int i = 0; i<tamanoPoblacion-1; i++)
			{
				if(mejor->aptitud > pob2[i]->aptitud)
				{
					mejora=true;
				}
			}
			if(mejora)
			{
				NoMejora = 0;
			}
			else
			{
				NoMejora++;
			}
			if(NoMejora >= nEval) //Reinicio
			{
				for(int i = 0; i<tamanoPoblacion-1; i++)
				{
					pob2[i]=generarSolucionRandom();
					pob2[i]->aptitud = evaluarSolucion(pob2[i]);
					cont++;
				}
				NoMejora = 0;
			}
			//termina si ha habido mejora

			for(int i=0;i<tamanoPoblacion-1;i++)//copiar la poblacion anterior
			{
				for(int j=0;j<data.n;j++)
				{
					pob[i]->VectorSolucion[j]=pob2[i]->VectorSolucion[j];
				}
				pob[i]->aptitud=pob2[i]->aptitud;
			}

			for(int i=0;i<data.n;i++)//anadir el elite a la poblacion
			{
				pob[tamanoPoblacion-1]->VectorSolucion[i]=mejor->VectorSolucion[i];
			}
			pob[tamanoPoblacion-1]->aptitud=mejor->aptitud;

			//cout<<"contador "<<cont<<endl;
			flujoSalida << cont << "\t"<< mejor->aptitud << endl;
		}while(cont<(5000*data.n));
		mejor=mejorSolucionPoblacion(pob,tamanoPoblacion);
		flujoSalida << cont << "\t"<< mejor->aptitud << endl;
		flujoSalida.close();

	}
	else //AGg
	{
		cout<<"AGg"<<endl;
		do{
			struct datosSolucionCPH * auxmejor=mejorSolucionPoblacion(pob, tamanoPoblacion); //guardar elite para siguiente generacion

			for(int i=0;i<data.n;i++)
			{
				mejor->VectorSolucion[i]=auxmejor->VectorSolucion[i];
			}
			mejor->aptitud=auxmejor->aptitud;

			/*for(int i=0;i<tamanoPoblacion;i++)
			{
				cout<<"aptitud "<<pob[i]->aptitud<<endl;
			}
			cout<<"apitudo MEJOR "<<mejor->aptitud<<endl;*/


			pob2=seleccionPorRuleta(pob, tamanoPoblacion, tamanoPoblacion-1);//llama a la funcion ruleta para generar los T-1 elementos mejores

			for (int i=0;i<tamanoPoblacion-1;i++)
			{
				r = ((double)rand())/RAND_MAX;
				if (r<=pCruce)//se llama a la funcion de cruce
				{
					int ind2=rand()%(tamanoPoblacion-1);//cogemos un individuo random
					operadorCruce(pob2[i],pob2[ind2]);
				}
			}
			for (int i=0;i<tamanoPoblacion-1;i++)
			{
				r = ((double)rand())/RAND_MAX;
				if(r<=pMutacion)//se hace mutacion
				{
					operadorMutacion(pob2[i]);
				}
			}

			for (int i=0;i<tamanoPoblacion-1; i++)//se recalcula la aptitud para los que tienen -1
			{
				if(pob2[i]->aptitud==-1)
				{
					pob2[i]->aptitud=evaluarSolucion(pob2[i]);
					cont++;
				}
			}


			bool mejora=false;//Comprobar mejora
			for(int i=0;i<tamanoPoblacion-1;i++)
			{
				if(pob2[i]->aptitud<mejor->aptitud)
				{
					mejora=true;
				}
			}

			if(mejora)
				NoMejora=0;
			else
				NoMejora++;


			if(NoMejora>=nEval)
			{
				for(int i=0; i<tamanoPoblacion-1; i++)
				{
					pob2[i]=generarSolucionRandom();
					pob2[i]->aptitud=evaluarSolucion(pob2[i]);
					cont++;

				}
				NoMejora=0;//Ha habido mejora asi que lo reinicio
			}

			for(int i=0;i<tamanoPoblacion-1;i++)
			{
				for(int j=0;j<data.n;j++)
				{
					pob[i]->VectorSolucion[j]=pob2[i]->VectorSolucion[j];
				}
				pob[i]->aptitud=pob2[i]->aptitud;
			}

			for(int j=0;j<data.n;j++)//se copia el elite para la siguiente generacion
			{
				pob[tamanoPoblacion-1]->VectorSolucion[j]=mejor->VectorSolucion[j];
			}
			pob[tamanoPoblacion-1]->aptitud=mejor->aptitud;
			flujoSalida << cont << "\t"<< mejor->aptitud << endl;

		}while(cont<(5000*data.n));
		mejor=mejorSolucionPoblacion(pob,tamanoPoblacion);
		flujoSalida << cont << "\t"<< mejor->aptitud << endl;
		flujoSalida.close();
		for(int i=0; i<tamanoPoblacion-1; i++)
		{
			liberarMemoriaSolucion(pob2[i]);
		}
	}
	return mejor;
}
void CPH::operadorMutacion(struct datosSolucionCPH *ind)
{
	int aux1=-1;
	int aux2=-1;
	do{
		aux1=rand()%data.n;
		aux2=rand()%data.n;
	}while(aux1==aux2);
	int cambio;
	//Simplemente cambio la solucion, a la hora de evaluar ya controlará si es válida desde el punto de vista de capacidad.
	cambio=ind->VectorSolucion[aux1];
	ind->VectorSolucion[aux1]=ind->VectorSolucion[aux2];
	ind->VectorSolucion[aux2]=cambio;
	ind->aptitud=-1;
}
void CPH::operadorCruce(struct datosSolucionCPH *ind1,struct datosSolucionCPH *ind2)
{
	float r=0;
	int aux=0;
	for(int i=0;i<data.n;i++)
	{

			if(ind1->VectorSolucion[i]<data.p && ind2->VectorSolucion[i]<data.p)
			{
				r=((double) rand()/RAND_MAX);
				if(r<0.5)//se cambia los indices de dos estructuras distintas
				{
					aux=ind1->VectorSolucion[i];
					ind1->VectorSolucion[i]=ind2->VectorSolucion[i];
					ind2->VectorSolucion[i]=aux;
					ind1->aptitud=-1;
					ind2->aptitud=-1;
				}
			}
	}

}
struct datosSolucionCPH ** CPH::seleccionPorTorneo(struct datosSolucionCPH **pob, int tamanoTorneo, int tamanoPoblacion, int numeroSeleccion)
{
	struct datosSolucionCPH ** pob2 = new struct datosSolucionCPH *[numeroSeleccion];
	int ind1, ind2;

	for(int i = 0; i<numeroSeleccion; i++)
	{
		ind1 = rand()%tamanoPoblacion; //se cogen dos individuos random
		ind2 = rand()%tamanoPoblacion;
		//Produce el torneo, según su aptitud se elige el mejor
		if(pob[ind1]->aptitud < pob[ind2]->aptitud)
		{
			pob2[i] = pob[ind1];
		}
		else if(pob[ind1]->aptitud > pob[ind2]->aptitud)
		{
			pob2[i] = pob[ind2];
		}
		else
		{
			pob2[i] = pob[ind1];
		}
	}

	return pob2;

}
struct datosSolucionCPH  ** CPH::seleccionPorRuleta(struct datosSolucionCPH **pob, int tamanoPoblacion, int numeroSeleccion)
{
	float * Aptitudes = new float [tamanoPoblacion];
	float Total = 0.0;
	struct datosSolucionCPH ** pobAux = new struct datosSolucionCPH *[numeroSeleccion];
	//se calcula la formula y se va metiendo en un vector
	for(int i = 0; i < tamanoPoblacion; i++)
	{
		Total += 1/pob[i]->aptitud;
		Aptitudes[i] = Total;
	}
	for(int i = 0; i < tamanoPoblacion; i++)
	{
		Aptitudes[i] = Aptitudes[i]/Total;
	}
	for(int i = 0; i < numeroSeleccion; i++)
	{
		pobAux[i]=reservaMemoriaSolucion();
	}

	//Si supera el random, se coge
	for(int i = 0; i < numeroSeleccion; i++)
	{
		float r = (double)rand()/RAND_MAX;
		for(int j = 0; j < tamanoPoblacion; j++)
		{
			if(Aptitudes[j] >= r)
			{
				for(int k = 0; k < data.n; k++)
				{
					pobAux[i]->VectorSolucion[k] = pob[j]->VectorSolucion[k];
				}
				pobAux[i]->aptitud = pob[j]->aptitud;
			}
		}
	}

return pobAux;
}

struct datosSolucionCPH * CPH::mejorSolucionPoblacion(struct datosSolucionCPH **pob, int tamanoPoblacion)
{
	struct datosSolucionCPH * mejor;
	mejor=reservaMemoriaSolucion();
	int aux=0;
	float comp=99999;
	for(int i=0;i<data.n;i++)
	{
		mejor->VectorSolucion[i]=0;
	}
	for(int i=0; i<tamanoPoblacion;i++)
	{
		//Mejor aptitud hasta i
		if(pob[i]->aptitud<comp)
		{
			comp=pob[i]->aptitud;
			aux=i;
		}
	}
	//Guardo
	for(int k=0; k<data.n; k++)
	{
		mejor->VectorSolucion[k]=pob[aux]->VectorSolucion[k];
	}
	mejor->aptitud=pob[aux]->aptitud;


	return mejor;
}

}
