#ifndef ALGORITMOGENETICO_H_
#define ALGORITMOGENETICO_H_

namespace mh {

template<typename DATOS_SOLUCION>
class AlgoritmoGenetico {
public:
	virtual DATOS_SOLUCION * aplicarAlgoritmoGenetico(int tamanoPoblacion, float pCruce, float pMutacion, int nEval, bool estacionario)=0;

private:
	virtual void operadorMutacion(DATOS_SOLUCION *ind)=0;
	virtual void operadorCruce(DATOS_SOLUCION *ind1,DATOS_SOLUCION *ind2)=0;
	virtual DATOS_SOLUCION ** seleccionPorTorneo(DATOS_SOLUCION **pob, int tamanoTorneo, int tamanoPoblacion, int numeroSeleccion)=0;
	virtual DATOS_SOLUCION ** seleccionPorRuleta(DATOS_SOLUCION **pob, int tamanoPoblacion, int numeroSeleccion)=0;
	virtual DATOS_SOLUCION * mejorSolucionPoblacion(DATOS_SOLUCION **pob, int tamanoPoblacion)=0;

protected:
	~AlgoritmoGenetico(void){};
};

}

#endif /* ALGORITMOGENETICO_H_ */
