#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
	int x;
	struct nodo *prox;
} Nodo;

int extraerUltimo(Nodo **plista){
	Nodo *pnodo = *plista; //puntero al primer nodo de la lista
	Nodo *prev = *plista;
	if (pnodo->prox == NULL) { //lista de un solo nodo
		int ans = pnodo->x;
		*plista = NULL; //el puntero a la lista apunta a null
		free(pnodo);
		return ans;
	}
	pnodo = pnodo->prox;
	while(1){
		if (pnodo->prox == NULL){ //el nodo en el que estoy es el ultimo
			int ans = pnodo->x;
			prev->prox = NULL; //el penulimo nodo apunta a null
			free(pnodo);
			return ans;
		}
		prev = pnodo;
		pnodo = pnodo->prox;

	}
}

