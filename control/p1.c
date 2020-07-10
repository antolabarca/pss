#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void desplazarDer(char *s, int n) {
	char *p;
	p=s;
	while(*p != '\0') { //voy hasta el final del string
		p++;
	} //me detengo y quedo apuntando a \0
	p--; //apunto al ultimo char != \0
	char *q;
	q=p;
	for (int i = 0; i < n; ++i) {
		q--;
	} //q queda apuntando en el char que se quiere copiar
	while (q!=s) { //hasta que q llegue al inicio del string
		*p=*q; //copio lo que habia en q a la direccion p
		p--;
		q--;
	} //q queda apuntando al inicio del str, aun no se hace la copia
	*p=*q;
	while (p!=s){ //hasta que p llegue al inicio del string
		p--;
		*p=' ';
	}//p queda en el inicio
}