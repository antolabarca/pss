#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>

#include "t4.h"

Nodo *lista(int x, Nodo *cola) {
  Nodo *nodo= malloc(sizeof(Nodo));
  if (nodo==NULL) {
    fprintf(stderr,
            "Se acabo la memoria.  Parace que Ud. no libera los nodos\n");
    exit(1);
  }
  nodo->x= x;
  nodo->prox= cola;
  return nodo;
}

Nodo *listaTest() {
  return lista(2, lista(4, lista(7, lista(8, lista(9, NULL)))));
}

int iguales(Nodo *lis1, Nodo *lis2) {
  if (lis1==NULL)
    return lis2==NULL;
  if (lis2==NULL)
    return 0;
  return lis1->x==lis2->x && iguales(lis1->prox, lis2->prox);
}

Nodo *lista29;
Nodo *lista789;
Nodo *lista24;

void test() {
  Nodo *head= listaTest();
  eliminarRango(&head,4,8);
  if (!iguales(head, lista29)) {
    fprintf(stderr, "Falla el primer test\n");
    while(lista29!=NULL){
      printf("\n");
      head=head->prox;
      lista29=lista29->prox;
    }
    exit(1);
  }

  eliminarRango(&head, 2, 9);
  if (head!=NULL) {
    fprintf(stderr, "Falla el segundo test\n");
    exit(1);
  }

  head= listaTest();
  eliminarRango(&head, 0, 5); 
  if (!iguales(head, lista789)) {
    fprintf(stderr, "Falla el 3er. test\n");
    exit(1);
  }
  eliminarRango(&head, 6, 10);
  if (head!=NULL) {
    fprintf(stderr, "Falla el 4to. test\n");
    exit(1);
  }

  head= listaTest();
  eliminarRango(&head, 5, 10); 
  if (!iguales(head, lista24)) {
    fprintf(stderr, "Falla el 5to. test\n");
    exit(1);
  }
  eliminarRango(&head, 2, 10);
  if (head!=NULL) {
    fprintf(stderr, "Falla el 6to. test\n");
    exit(1);
  }
}

#define NTESTS 25000000
int main() {
  lista29=  lista(2, lista(9, NULL));
  lista789= lista(7, lista(8, lista(9, NULL)));
  lista24= lista(2, lista(4, NULL));
  struct rusage r;

  for (int i= 0; i<NTESTS; i++) {
    if (i%(NTESTS/100)==0) {
      getrusage(RUSAGE_SELF, &r);
      long kilos= r.ru_maxrss;
      int megas= kilos/1024;
      int gigas= megas/1024;
      printf("maximum resident set size= ");
      if (gigas!=0) {
        fprintf(stderr, "Uso excesivo de memoria.  Libero los nodos?\n");
        exit(1);
      }
      if (megas!=0) printf("%d megabytes ", megas);
      printf("%ld kilobytes\n", kilos%1024);
    }
    test();
  }

  printf("\nFelicitaciones!  Paso todos los tests\n");

  return 0;
}
