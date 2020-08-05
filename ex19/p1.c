#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void elimUltPal(char *s){ //recibe un puntero al 1er char
	char *p;
	char *ini;

	p=s; //p apunta al mismo string
	ini=s; //ini apunta al inicio del string

	while(*p != '\0'){
		p++;
	} //p queda apuntando a \0
	p--; //p apunta al ultimo char de verdad

	char* fin;
	fin = p; //fin apunta al ultimo char

	while(*p==' ' && p!=ini){
		p--;
	} //p apunta a la ultima letra de la ultima palabra, o a ini
	while(*p!=' ' && p!=ini){
		p--;
	} //p apunta al ultimo espacio antes de la ultima palabra, o a ini

	while(p != ini){
		*fin = *p;
		fin--;
		p--;
	} //termino con p en la posicion inicial del string
	*fin = *p; //se copia el primer char del string en la posicion fin

	while(fin != ini){
		fin--;
		*fin = ' ';
	} //fin termina en la 1a posicion del string
	
}


// Tests del enunciado
int main(int argc, char const *argv[])
{
  char s[] = "hola   que tal  ";
  elimUltPal(s);
  if (strcmp(s,"     hola   que ") == 0) {
    printf("Test 1 correcto.\n");
  }
  elimUltPal(s);
  if (strcmp(s,"         hola   ") == 0) {
    printf("Test 2 correcto.\n");
  }
  elimUltPal(s);
  if (strcmp(s,"                ") == 0) {
    printf("Test 3 correcto.\n");
  }
  elimUltPal(s);
  if (strcmp(s,"                ") == 0) {
    printf("Test 4 correcto.\n");
  }
  return 0;
}