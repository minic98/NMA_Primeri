#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int vectAdd(double *c, double *a, double *b, int n) {
    int thread_num;

    #pragma omp parallel for
    for(int i=0; i<n; i++) {
        c[i] = a[i] + b[i];
        thread_num = omp_get_num_threads();
    }

    return thread_num;
}

int main() {
    int n = 10000; // Vector size
    int num_additions = 10000; // Num of additions
    int thread_num;

    double *a = (double *)malloc(n*sizeof(double));
    double *b = (double *)malloc(n*sizeof(double));
    double *c = (double *)malloc(n*sizeof(double));

    // Vector a and b init
    for(int i=0; i<n; i++){
        a[i] = i;
        b[i] = n + i;
    }

    double start_time = omp_get_wtime();
    for(int i=0; i<num_additions; i++){
        int tmp;
        tmp = vectAdd(c, a, b, n);
        thread_num = thread_num > tmp ? thread_num : tmp;
    }
    double end_time = omp_get_wtime();

    double elapsed_time = end_time - start_time;

    printf("Vektorsko sabiranje se izvrsilo %0d puta sa vektorima velicine %0d za %.4f ", num_additions, n, elapsed_time); 
    printf("sekundi koristeci %0d threads. \n", thread_num);
    
    // Free allocated space
    free(a);
    free(b);
    free(c);

    return 0;
}
