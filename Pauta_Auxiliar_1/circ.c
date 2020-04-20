#include <stdio.h>
#include "get_pi.h"

double get_perimetro(double radio) {
    return 2 * radio * get_pi(2);
}

int main() {
    double perimetro = get_perimetro(3.9);
    printf("%f\n", perimetro);

    return 0;
}
