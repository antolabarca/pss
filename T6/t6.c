#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

typedef unsigned long long Set;

typedef struct {
	int* a;
	int n;
	Set ini, fin;
	Set ans;
} Args;

Set buscar_rango(int* a, int n, Set ini, Set fin){
	for (Set k = ini; k <= fin; k++) {  // k es el mapa de bits para el subconjunto { a[i] | bit ki de k es 1 }    
		long long sum= 0;
		for (int i = 0; i < n; i++) {    //n es la cantidad de numeros de a[]  
			if ( k & ((Set)1<<i) ){ // si bit ki de k es 1 
				sum+= a[i];
			}
		}
		if (sum==0 && k!=0) {  // exito: el subconjunto suma 0
			return k;  // y el mapa de bits para el subconjunto es k
		}
	}
	return 0;        // no existe subconjunto que sume 0
}

//funcion del thread
void* thread_fun(void *p){
	Args *args = (Args *) p;
	int* a = args->a;
	int n = args -> n;
	Set ini = args -> ini;
	Set fin = args -> fin;
	args -> ans = buscar_rango(a, n, ini, fin);
	return NULL;
}


Set buscar(int a[], int n){
	Set comb= (1<<(n-1)<<1)-1; // 2n-1: nº de combinaciones
	pthread_t t[8];
	Args args[8];
	Set ret = 0; 
	Set h = (comb+8)/8;
	for (int i = 0; i < 8; ++i){
	 	args[i].a = a;
	 	args[i].n = n;
	 	args[i].ini = i*h;
	 	args[i].fin = (i+1)*h - 1;
	 	args[i].ans = 0;
	 	pthread_create(&t[i], NULL, thread_fun, &args[i]); //en args[i] se esta guardando el bitmap
	}
	for (int i = 0; i < 8; ++i){
	 	pthread_join(t[i], NULL);
	 	if (args[i].ans != 0){
	 		ret = args[i].ans;
	 	}
	}
	return ret;
}