#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int mtxMul_farLoopTogether(double **c, double **a, double **b, int n) {
    int thread_num;

    #pragma omp parallel for collapse (2)
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            c[i][j] = 0;
            for(int k=0; k<n; k++) {
                thread_num = omp_get_num_threads();
                c[i][j] = c[i][j] + a[i][k] * b[k][j];
            }
        }
    }

    return thread_num;
}

int mtxMul_farLoopSeparate(double **c, double **a, double **b, int n) {
    int thread_num;

    #pragma omp parallel for
    for(int i=0; i<n; i++) {
        #pragma omp parallel for
        for(int j=0; j<n; j++) {
            c[i][j] = 0;
            for(int k=0; k<n; k++) {
                thread_num = omp_get_num_threads();
                c[i][j] = c[i][j] + a[i][k] * b[k][j];
            }
        }
    }

    return thread_num;
}

int main() {
    int n = 1000; // Vector size
    int thread_num;
    int tmp;
    double start_time;
    double end_time;
    double elapsed_time;

    double **a = malloc(n*sizeof(double *));
    double **b = malloc(n*sizeof(double *));
    double **c = malloc(n*sizeof(double *));
    for (int i=0; i<n; i++) {
        a[i] = malloc(n*sizeof(double));
        b[i] = malloc(n*sizeof(double));
        c[i] = malloc(n*sizeof(double));
    }

    // Matrix a and b init
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            a[i][j] = i + j;
            b[i][j] = i - j;
            c[i][j] = 0.0;
        }

    start_time = omp_get_wtime();
    tmp;
    tmp = mtxMul_farLoopTogether(c, a, b, n);
    thread_num = thread_num > tmp ? thread_num : tmp;
    end_time = omp_get_wtime();
    elapsed_time = end_time - start_time;

    printf("Matricno mnozenje se izvrsilo sa matricama velicine %0d za %.4f ", n, elapsed_time); 
    printf("sekundi koristeci %0d threads sa odvojenim petljama zajedno. \n", thread_num);
    
    // Part of the code that uses far loops separate
    start_time = omp_get_wtime();
    tmp;
    tmp = mtxMul_farLoopSeparate(c, a, b, n);
    thread_num = thread_num > tmp ? thread_num : tmp;
    end_time = omp_get_wtime();
    elapsed_time = end_time - start_time;

    printf("Matricno mnozenje se izvrsilo sa matricama velicine %0d za %.4f ", n, elapsed_time); 
    printf("sekundi koristeci %0d threads sa odvojenim petljama odvojeno. \n", thread_num);    
    // Free allocated space
    for (int i=0; i<n; i++) {
        free(a[i]);
        free(b[i]);
        free(c[i]);
    }
    free(a);
    free(b);
    free(c);

    return 0;
}
