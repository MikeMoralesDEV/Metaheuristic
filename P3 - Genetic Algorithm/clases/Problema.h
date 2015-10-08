#ifndef PROBLEMA_H_
#define PROBLEMA_H_

namespace mh {


template<typename DATOS_INSTANCIA, typename DATOS_SOLUCION>
class Problema {
public:
	//~Problema;
	virtual int leerInstancia(char * archivo)=0;
	virtual float evaluarSolucion(DATOS_SOLUCION * sol)=0;
	virtual DATOS_SOLUCION * generarSolucionRandom()=0;
	virtual void imprimirSolucion(DATOS_SOLUCION * sol)=0;
	virtual void imprimirInstancia()=0;
	virtual void liberarMemoriaSolucion(DATOS_SOLUCION *sol)=0;
protected:
	DATOS_INSTANCIA data;
	DATOS_SOLUCION solucion;
	virtual int reservarMemoria()=0;
	virtual void liberarMemoria()=0;
	virtual DATOS_SOLUCION *reservaMemoriaSolucion()=0;
};

}

#endif /* PROBLEMA_H_ */
