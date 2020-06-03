#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char izq[10], der[10], llave[20], val[59], newline;
} Definicion;

Definicion defi;
FILE *in;

void buscar(int linea, char *word){
	if (linea==-1) {
		printf("palabra no encontrada \n");
		exit(1);
	}
	fseek(in, linea*100, SEEK_SET);
	fread(&defi, sizeof(Definicion),1,in);
	int n= strlen(word);
	int comp = strncmp(word,defi.llave,n);
	if (comp == 0) {
		printf("%s",defi.val);
		exit(1);
	}
	if (comp < 0) { //word < defi.llave
		linea=atoi(defi.izq);
		buscar(linea, word);
	}
	if (comp > 0) { //if word > defi.llave
		linea=atoi(defi.der);
		buscar(linea,word);
	}
}

int main(int argc, char *argv[]){
	in = fopen(argv[1], "r");
	if (in==NULL) {
		perror(argv[1]);
		exit(1);
	}
	buscar(0, argv[2]);
	return 0;
}