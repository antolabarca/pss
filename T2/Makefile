# Instrucciones
# =============
#
# Cree el archivo t2.c y programe ahi la funcion insertar_bits.
# No modifique los demas archivos.
# Comience el archivo t2.c como se indica en t2.c.plantilla
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
# $ ./test-t2
#
# El programa de prueba le indicara cual test falla o lo felicitara si
# paso todos los tests.  Ademas correra un benchmark para comparar la
# eficiencia de su solucion con operadores de bits con mi solucion con
# * / y %.  Este benchmark no es valido porque el programa fue compilado
# para depuracion, lo que lo hace mucho mas lento.
#
# Recompile el programa con las opciones de optimizacion con el comando:
#
# $ make opt
#
# Esto recompila el programa reemplazando la opcion -g (depuracion) por -O2
# (optimizacion) y ejecuta el programa nuevamente.  Normalmente el speed up
# seria 3 aproximadamente.
#
# Para borrar todos los archivos generados (incluyendo binarios):
# $ make clean

CFLAGS= -g -Wall -pedantic -std=c99
LDFLAGS= -g

all: test-t2

test-t2: test-t2.o t2.o

test-t2.o t2.o: t2.h

opt:
	make clean
	make "CFLAGS=-O2 -Wall -pedantic -std=c99"
	./test-t2

clean:
	rm -f *.o test-t2
