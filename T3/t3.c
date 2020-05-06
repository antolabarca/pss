#include <string.h>
#include <stdlib.h>

#include "t3.h"

char *recorte(char *str){ /*recibe un string, aka puntero a un char*/
	char *s;
	s=malloc(sizeof(char)*(strlen(str)+1));
	char *t;
	t=s;
	char *p=str;
	while(*p == ' '){
		p++;
	}
	while(*p != '\0'){
		*s=*p;
		s++;
		p++;
	}
	p--;
	s--;
	while(*p == ' '){
		p--;
		s--;
	}
	s++;
	*s='\0';
	return t;
}


void recortar(char **pstr){ /*recibe puntero a un string, aka puntero a un puntero a un char*/
	char s[strlen(*pstr)+1];
	char *t;
	t=s;
	char *u;
	u=s;
	char *p = *pstr; //p apunta a pstr
	while(*p == ' '){ //recorro pstr hasta encontrar algo distinto a " "
		p++;
	} //p apunta a la primera pos que no es " "
	while(*p != '\0'){ //recorro pstr hasta encontrar "\0"
		*t=*p; //en s se escriben las cosas distintas a "\0"
		t++;
		p++;
	} // t y p quedan apuntando a donde estaría \0
	t--;
	p--; //t y p quedan apuntando uno antes de \0
	while(*t == ' '){ //mientras en t hay " "
		p--; //se va atrás
		t--;
	} //t y p quedan en el ultimo char distinto de " "
	t++; //t está en el primer " "
	*t='\0'; // se pone \0 donde estaba el primer " "
	char *q = *pstr; // q apunta al str que se quiere cambiar
	while(*u != '\0'){ //u apunta al principio de s
		*q=*u; // en pstr (q) se va escribiendo u, mientras no es \0
		q++;
		u++;
	} // q y u apuntan a donde debería estar \0
	*q='\0';
	//ir guardando lo que quiero en s, igual que en recorte
	//guardar ese nuevo string en la memoria **pstr
}