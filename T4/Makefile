# Instrucciones
# =============
#
# Cree el archivo t4.c y programe ahi la o las funciones pedidas.
# No modifique los demas archivos.
# Comience el archivo t4.c como se indica en t4.c.plantilla
#
# Su tarea ya esta compilada con la opcion -g, que es necesaria para
# que use gdb o ddd para depurar los errores de programacion.
#
# Para compilar ingrese el comando:
#
# $ make
#
# Resuelva todos los errores y warnings de la compilacion.
# Cuando la compilacion sea exitosa, ejecute el programa de prueba con:
#
# $ ./test-t4
#
# El programa de prueba le indicara cual test falla o lo felicitara si
# paso todos los tests.  Ademas le indicara el uso de memoria de su
# programa.  Podria subir en los primeros mensajes pero luego rapidamente
# se debe mantener constante.  En mi maquina ocupo 1 mega y 720 kilobytes.
#
# Recompile el programa con las opciones de optimizacion con el comando:
#
# $ make opt
#
# Esto recompila el programa reemplazando la opcion -g (depuracion) por -O2
# (optimizacion) y ejecuta el programa nuevamente.  Debe pasar el test
# de prueba nuevamente.
#
# Para borrar todos los archivos generados (incluyendo binarios):
# $ make clean

CFLAGS= -g -Wall -pedantic -std=c99
LDFLAGS= -g -pthread

all: test-t4

test-t4: t4.o test-t4.o

t4.o test-t4.o: t4.h

opt:
	make clean
	make "CFLAGS=-O2 -Wall -pedantic -std=c99"
	./test-t4
	make clean

clean:
	rm -f *.o
	rm -f test-t4
