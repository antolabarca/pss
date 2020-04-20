#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#include "t2.h"

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

uint potencia(uint x, uint n) {
  if (n==0)
    return 1;
  else if (n%2==0)
    return potencia(x*x, n/2);
  else
    return x*potencia(x*x, n/2);
}

// insertar_bits implementado con multiplicaciones y divisiones
uint insertar_lento(uint x, int pos, uint y, int len) {
  // Ejemplo: x es 0b10111, pos es 2, y es 0b01110, len es 5
  uint dos_elev_pos= potencia(2, pos); // 2^2= 4
  uint prefijo= x / dos_elev_pos; // 0b101 (a la izquierda de la insercion)
  uint sufijo= x % dos_elev_pos;  // 0b11 (a la derecha de la insercion)
  uint pref_concat_y= prefijo * potencia(2, len) + y; // 0b10100000 + 0b01110
  uint res= pref_concat_y * dos_elev_pos + sufijo;
  return res;
}

// Insertar es el tipo de las funciones que insertan bits.  Hay 2
// funciones que pertenecen a este tipo: insertar_lento e insertar_bits
typedef uint (*Insertar)(uint x, int pos, uint y, int len);

void test_insertar(Insertar insertar) {

  if ((*insertar)(0x2, 0, 1, 1)!= 5) {
    fprintf(stderr, "insertar_bits(0b0010, 0 , 0b1, 1) != 0b0101\n");
    exit(1);
  }

  if ((*insertar)(0x20000002, 31, 1, 1)!= 0xa0000002) {
    fprintf(stderr, "insertar_bits(0b0010...0010, 31 , 0b1, 1) != "
                    "0b1010...0010\n");
    exit(1);
  }

  if ((*insertar)(0x2d, 3, 0x0, 2)!=0xa5) {
    fprintf(stderr, "insertar_bits(0b10 1101, 3, 0b00, 2) != 0b1010 0101\n");
    exit(1);
  }

  if ((*insertar)(0x37, 0, 0x3, 3)!=0x1bb) {
    fprintf(stderr, "insertar_bits(0b11 0111, 0, 0b011, 3) != 0b1 1011 1011\n");
    exit(1);
  }

  if ((*insertar)(0x17, 2, 0x0e, 5)!=0x2bb) {
    fprintf(stderr, "insertar_bits(0b1 0111, 2, 0b01110, 5) es 0b10 1011 1011\n");
    exit(1);
  }
}

int bench(Insertar insertar, char *metodo) {
  resetTime();
  for (int i= 0; i<10000000; i++) {
    (*insertar)(0x2, 0, 1, 1);
    (*insertar)(0x20000002, 31, 1, 1);
    (*insertar)(0x2d, 3, 0x0, 2);
    (*insertar)(0x37, 0, 0x3, 3);
    (*insertar)(0x17, 2, 0x0e, 5);
    (*insertar)(0x2, 0, 1, 1);
    (*insertar)(0x20000002, 31, 1, 1);
    (*insertar)(0x2d, 3, 0x0, 2);
    (*insertar)(0x37, 0, 0x3, 3);
    (*insertar)(0x17, 2, 0x0e, 5);
    (*insertar)(0x2, 0, 1, 1);
    (*insertar)(0x20000002, 31, 1, 1);
    (*insertar)(0x2d, 3, 0x0, 2);
    (*insertar)(0x37, 0, 0x3, 3);
    (*insertar)(0x17, 2, 0x0e, 5);
    (*insertar)(0x2, 0, 1, 1);
    (*insertar)(0x20000002, 31, 1, 1);
    (*insertar)(0x2d, 3, 0x0, 2);
    (*insertar)(0x37, 0, 0x3, 3);
    (*insertar)(0x17, 2, 0x0e, 5);
    (*insertar)(0x2, 0, 1, 1);
    (*insertar)(0x20000002, 31, 1, 1);
    (*insertar)(0x2d, 3, 0x0, 2);
    (*insertar)(0x37, 0, 0x3, 3);
    (*insertar)(0x17, 2, 0x0e, 5);
  }
  int time= getTime();
  printf("Tiempo con metodo %s = %d milisegundos\n", metodo, time);
  return time;
}

int main() {
  test_insertar(insertar_lento);
  printf("Test de insert_bits\n");
  test_insertar(insertar_bits);
  printf("Felicitaciones: paso todos los tests\n");

  printf("Benchmarks\n");
  int lento= bench(insertar_lento, "con multiplicaciones/divisiones");
  int bits= bench(insertar_bits, "con operadores de bits");
  printf("speed up= %f\n", (double)lento/bits);

  return 0;
}
