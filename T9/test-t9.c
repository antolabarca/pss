#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "maleta.h"

int random0or1() {
  long int r= random();
  return r&1;
}

int contarArticulos(double w[], double v[], int z[], int n, double *pw, double *pval) {
  int cnt= 0;
  *pw= 0;
  *pval= 0;
  for (int j=0; j<n; j++) {
    if (z[j]) {
      cnt++;
      *pw += w[j];
      *pval += v[j];
    }
  }
  return cnt;
}

int main() {

  printf("Test 1: Un ejemplo pequeño\n");
  {
    int n= 5;
    double maxW= 10;
    int k= 80000000;
    double w[]= {5, 4, 2, 4, 5};
    double v[]= {100, 110, 200, 150, 180};
    int z[n];
    printf("Calculando\n");
    double best= llenarMaleta(w, v, z, n, maxW, k);
    double sumW, sumVal;
    int nsel= contarArticulos(w, v, z, n, &sumW, &sumVal);
    if (fabs(sumVal-best)>0.000001) {
      fprintf(stderr, "El valor retornado no coincide con el valor calculado para z %g != %g\n",
              best, sumVal);
      exit(1);
    }
    printf("k= %d  numero de articulos seleccionados= %d  valor= %g peso= %g\n",
           k, nsel, best, sumW);
    if (best>=0 && (nsel!=3 || best!=460 || sumW!=10)) {
      fprintf(stderr, "La solucion debio ser 3 articulos con valor 460 y peso 10\n");
      exit(1);
    }
    printf("Test 1 aprobado\n");
    printf("\n--------------------------------------------------\n\n");
  }

  printf("Test 2: Un ejemplo grande con n=32\n");
  {
    int n= 32;
    double maxW= 300;
    int k= 10000000;
    double w[]= { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
                 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32 };

    double v[]= {32.1, 31.5, 30.0, 29.8, 28.3, 27.7, 26.2, 25.3, 24.9, 23.6, 22.5,
                 21.0, 20.6, 19.4, 18.9, 17.3, 16.8, 15.1, 14.7, 13.5, 12.2, 11.8,
                 10.3, 9.1, 8.7, 7.3, 6.1, 5.9, 4.2, 3.6, 2.8, 1.7};
 
    int z[n];
    double sumW, sumVal;

    printf("Calculando con k= %d combinaciones\n", k);
    double best= llenarMaleta(w, v, z, n, maxW, k);
    int nsel= contarArticulos(w, v, z, n, &sumW, &sumVal);
    if (fabs(sumVal-best)>0.000001) {
      fprintf(stderr, "El valor retornado no coincide con el valor calculado para z %g != %g\n",
              best, sumVal);
      exit(1);
    }
    printf("k= %d  numero de articulos seleccionados= %d  valor= %g peso= %g\n",
           k, nsel, best, sumW);
    if (sumW>maxW) {
       fprintf(stderr, "Error: excede el peso limite\n");
       exit(1);
    }
    if (best>=0 && best < 480) {
       fprintf(stderr, "Error: debio haber encontrado un conjunto de mejor valor\n");
       exit(1);
    }
  }
  
  return 0;
}
