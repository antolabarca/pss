#include <stdio.h>
#include <stdlib.h>

#include "t4.h"


void eliminarRango(Nodo **phead, double y, double z){
	Nodo *pnodo = *phead;
	Nodo **ppnodo = phead;
	Nodo *p0=NULL;
	Nodo *p1;
	Nodo *p2;
	while (pnodo->x < y && pnodo != NULL) {
		ppnodo = & pnodo->prox;
		p0 = pnodo;
		pnodo = *ppnodo;
	} //p0 es el ultimo nodo bueno, pnodo queda siendo el primero malo
	while (1) {
		if (pnodo->x > z) {
			p2=pnodo; //p2 apunta al primer nodo despues del rango que hay que borrar
			break;
		}
		p1= pnodo;
		if (pnodo->prox == NULL) {
			free(p1);
			p2 = NULL;
			break;
		}
		ppnodo = &pnodo->prox;
		pnodo = *ppnodo;
		free(p1);
		
	}
	if (p0==NULL) { //aka nunca se entro al primer while, el primer nodo ya tenia que borrarse
		*phead = p2;
	}
	else { //habia nodos buenos al principio, el ultimo de ellos debe apuntar al primer bueno del 3er trozo de la lista
		p0->prox = p2;
	}
}
