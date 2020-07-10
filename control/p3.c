#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


enum { LEFT= 0, RIGHT= 1 };

int busy[2]= { 0, 0 }; // Ambas mitades libres

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int halfLock() {
	pthread_mutex_lock(&m); 
	while(busy[LEFT]&&busy[RIGHT])
		pthread_cond_wait(&cond, &m);
	int side= busy[LEFT] ? RIGHT : LEFT;
	busy[side]= 1;
	pthread_cond_broadcast(&cond);
	pthread_mutex_unlock(&m);
	return side;
}

void halfUnlock(int side) {
	pthread_mutex_lock(&m);
	busy[side]= 0;
	pthread_cond_broadcast(&cond);
	pthread_mutex_unlock(&m);
}

void fullLock() {
	pthread_mutex_lock(&m);
	while (busy[LEFT] || busy[RIGHT])
		pthread_cond_wait(&cond, &m);
	busy[LEFT]= busy[RIGHT]= 1;
	pthread_cond_broadcast(&cond);
	pthread_mutex_unlock(&m);
}

void fullUnlock() { 
	pthread_mutex_lock(&m);
	busy[LEFT]= busy[RIGHT]= 0;
	pthread_cond_broadcast(&cond);
	pthread_mutex_unlock(&m);
}

