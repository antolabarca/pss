#include <math.h>

double get_pi(int decimales) {
    double pi = 3.1415926535;
    double potencia = pow(10, decimales);
    return floorf(pi * potencia) / potencia;
}
