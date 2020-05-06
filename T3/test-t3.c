#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

#include "t3.h"

// ----------------------------------------------------
// Funcion que entrega el tiempo transcurrido desde el lanzamiento del
// programa en milisegundos

static int time0= 0;

static int getTime0() {
    struct timeval Timeval;
    gettimeofday(&Timeval, NULL);
    return Timeval.tv_sec*1000+Timeval.tv_usec/1000;
}

void resetTime() {
  time0= getTime0();
}

int getTime() {
  return getTime0()-time0;
}

// ----------------------------------------------------

void test_recorte() {
  char *u= recorte("  ");
  if (strcmp(u, "")!=0) {
    fprintf(stderr, "u no es \"\": %s\n", u);
    exit(1);
  }
  free(u); 
  char *r= recorte("  hola  que tal   ");
  if (strcmp(r, "hola  que tal")!=0) {
    fprintf(stderr, "r no es \"hola  que tal\": .%s.\n", r);
    exit(1);
  }
  free(r);
  char *t= recorte("bonjour    la vie    ");
  if (strcmp(t, "bonjour    la vie")!=0) {
    fprintf(stderr, "t no es \"bonjour    la vie\": .%s.\n", r);
    exit(1);
  }
  char *v= recorte(" hello");
  if (strcmp(v, "hello")!=0) {
    fprintf(stderr, "v no es \"hello\": .%s.\n", r);
    exit(1);
  }
  char *w= recorte("ciao");
  if (strcmp(w, "ciao")!=0) {
    fprintf(stderr, "w no es \"ciao\": .%s.\n", r);
    exit(1);
  }
}

void test_recortar_solido(char *src, char *ref) {
  // Hay almacenamiento extra antes y despues de "  hola  que tal   "
  char t[100];
  strcpy(t, "0123456789"); // Quedan antes de src
  int len_t= strlen(t);
  int len_src= strlen(src);
  char *u= t+len_t;
  strcpy(u, src);
  strcpy(u+len_src+1,"abcdef012345"); // Queda despues de "  hola  que tal   "
  recortar(&u);
  if (strcmp(u, ref)!=0) {
    fprintf(stderr, "u no es \"%s\": \"%s\"\n", ref, u);
    exit(1);
  }
  if (strncmp(t, "0123456789", 10)!=0) {
    fprintf(stderr, "Ud. modifico caracteres que venian antes de u\n");
    exit(1);
  }
  if (strcmp(t+len_t+len_src+1, "abcdef012345")!=0) {
    fprintf(stderr, "Ud. modifico caracteres que venian despues de u\n");
    exit(1);
  }
}

void test_recortar() {
  test_recortar_solido("", "");
  test_recortar_solido("  hola  que tal   ", "hola  que tal");
  test_recortar_solido("bonjour    la vie    ", "bonjour    la vie");
  test_recortar_solido(" hello", "hello");
  test_recortar_solido("ciao", "ciao");
}

void bench_recorte() {
  char u[]= "  ";
  char r[]= "  hola  que tal   ";
  char t[]= "bonjour    la vie    ";
  char v[]= " hello";
  char w[]= "ciao";
  char *s;
  s= recorte(u); free(s);
  s= recorte(r); free(s);
  s= recorte(t); free(s);
  s= recorte(v); free(s);
  s= recorte(w); free(s);
}

void bench_recortar() {
  char u[]= "  ";
  char r[]= "  hola  que tal   ";
  char t[]= "bonjour    la vie    ";
  char v[]= " hello";
  char w[]= "ciao";
  char *s;
  s= u; recortar(&s);
  s= r; recortar(&s);
  s= t; recortar(&s);
  s= v; recortar(&s);
  s= w; recortar(&s);
} 

#define REPS 1000000

typedef void (*TestFun)();

int bench(TestFun fun, char *metodo) {
  resetTime();
  for (int i= 0; i<REPS; i++) {
    (*fun)();
    (*fun)();
    (*fun)();
    (*fun)();
    (*fun)();
    (*fun)();
    (*fun)();
    (*fun)();
    (*fun)();
    (*fun)();
    (*fun)();
    (*fun)();
  }
  int time= getTime();
  printf("Tiempo con funcion %s = %d milisegundos\n", metodo, time);
  return time;
}

int main() {
  printf("Test de recorte\n");
  test_recorte();
  printf("Bien!\n");
  printf("Test de recortar\n");
  test_recortar();
  printf("Bien!\n");
  printf("Felicitaciones!  Los tests funcionan bien.\n");

  printf("Benchmarks\n");
  int t_recorte= bench(bench_recorte, "recorte");
  int t_recortar= bench(bench_recortar, "recortar");
  printf("speed up= %f\n", (double)t_recorte/t_recortar);

  return 0;
}

