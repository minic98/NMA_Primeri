#include <stdio.h>
#include <omp.h>

long fib(int n) { return (n < 2 ? 1 : fib(n - 1) + fib(n - 2)); }

int main(int argc, char* argv[]) {
    int max; 

    printf("Unestie maksimalnu vrednost: ");
    scanf("%d", &max);
    
    { // Primer 4.2
        #pragma omp parallel
        #pragma omp single
        for (int n = 1; n <= max; n++)
            #pragma omp task
            printf("4.2 | Thread %d: %d %ld\n", omp_get_thread_num(), n, fib(n));
    }

    { // Primer 4.3
        #pragma omp parallel
        #pragma omp single
        for (int n = max; n >= 1; n--)
            #pragma omp task
            printf("4.3 | Thread %d: %d %ld\n", omp_get_thread_num(), n, fib(n));
    }

    return 0;
}