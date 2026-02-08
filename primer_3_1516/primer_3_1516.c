#include <stdio.h>
#include <math.h>
#include <omp.h>

int main(int argc, char* argv[]) {
    int intervals;
    double integral = 0.0;
    double x, dx, pi;

    printf("Unesite vrednost za intervals: ");
    scanf("%d", &intervals);
    x = 0;
    dx = 1.0 / intervals;

    // primer 3.15
    #pragma omp parallel for reduction(+:integral)
    for(int i=0; i<intervals; i++) {
        x = i * dx;
        double fx = sqrt(1.0 - x * x);
        integral = integral + fx * dx;
    }

    pi = 4 * integral;
    printf("3.15 | Vrednost pi=%1.20f \n", pi);

    // Primer 3.16 - Petlja se ne moze paralelizovati
    #pragma omp parallel for reduction(+:integral)
    for(int i=0; i<intervals; i++) {
        double fx = sqrt(1.0 - x * x);
        integral = integral + fx * dx;
        x += dx;
    }

    pi = 4 * integral;
    printf("3.16 | Vrednost pi=%1.20f \n", pi);



    return 0;
}