#ifndef BUSQUEDALOCAL_H_
#define BUSQUEDALOCAL_H_

using namespace std;
namespace clases {

// Plantilla de clase
// Establece la estructura de las clases que representar�n a los problemas (MMDP, CWP y CPH)
// Estas clases deber�n heredar de Problema y definir los m�todos virtuales necesarios
// Cada una de estas clases deber� definir dos estructuras, una para los datos de la instancia
// y otra para los datos de la soluci�n. Estas estructuras son las que aparecen como argumentos
// en la plantilla.
template<typename DATOS_INSTANCIA, typename DATOS_SOLUCION>
class BusquedaLocal
{
    public:

    virtual DATOS_SOLUCION * aplicarBusquedaLocal(struct datosSolucionMMDP *sol, bool firstImprovement)=0;
	virtual int leerInstancia(char * archivo)=0;
	virtual float evaluarSolucion(DATOS_SOLUCION * sol)=0;
	virtual DATOS_SOLUCION * generarSolucionRandom()=0;
	virtual void imprimirSolucion(DATOS_SOLUCION * sol)=0;
	virtual void imprimirInstancia()=0;
	virtual void liberarMemoriaSolucion(DATOS_SOLUCION *sol)=0;
protected:
	DATOS_INSTANCIA data;
	virtual int reservarMemoria()=0;
	virtual void liberarMemoria()=0;
};
}

#endif // BUSQUEDALOCAL_H_



//virtual DATOS_SOLUCION * aplicarEnfriamientoSimulado(struct datosSolucionMMDP *sol, float tFinal, float gamma, int iterRelaTamano)=0;
