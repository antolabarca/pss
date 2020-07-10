#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>


typedef struct {
	int *a;
	int ini, fin;
	int ans;
} Args;



//funcion que retorna el maximo de un rango
int max_rango(int *a, int ini, int fin){
	int max = MININT;
	for (int i = ini; i <= fin; ++i){
		if(a[i]>max){
			max=a[i];
		}
	}
	return max;
}

//funcion del thread
void *thread_fun(void *p){
	Args *args = (Args *) p;
	int *a = args->a;
	int ini = args->ini;
	int fin = args->fin;
	args->ans = max_rango(a, ini, fin);
	return NULL;
}

//funcion principal
int maxArreglo(int a[], int n, int p){
	int max = MININT;
	pthread_t threads[p]; //un arreglo para los p threads
	Args args[p]; //un arreglo para los p args
	int s = n/p;
	for (int i = 0; i < p; ++i) { //se crean los p threads
		args[i].a = a;
		args[i].ini = i*s;
		args[i].fin = (i+1)*s - 1;
		args[i].ans = 0;
		pthread_create(&threads[i], NULL, thread_fun, &args[i]);
	}
	for (int i = 0; i < p; ++i){
		pthread_join(threads[i], NULL);
		if (args[i].ans > max){
			max = args[i].ans;
		}
	}
	return max;
}

