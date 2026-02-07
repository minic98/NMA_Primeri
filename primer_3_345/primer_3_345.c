#include <stdio.h>
#include <omp.h>

// Paralelizacija petlji

int main(int argc, char* argv[]) {
    int max;
    int nested_status = omp_get_nested();

    // Check if nested parallelism is enabled. 
    // If DISABLED try enabling.
    // If enabling fails - return 0 and exit.
    if(!nested_status) {
        printf("This example requires nested parallelism.\n");
        printf("Nested Parallelism DISABLED! Trying to enable it by running: omp_set_nested(1) \n. \n. \n. \n");
        omp_set_nested(1);
        nested_status = omp_get_nested();

        if(!nested_status) {
            printf("Failed to enable nested parallelism. Enable it by setting env variable: \n");
            printf("export OMP_NESTED=true \n");
            printf("Exiting... \n");
            return 0;
        }
    } 

    printf("Unesite maksimalnu vrednost: ");
    scanf("%d", &max);

    printf("\n   Primer 3.3\n");
    #pragma omp parallel for
    for(int i=0; i<max; i++) {
        for(int j=0; j<max; j++) {
            printf("Thread: %d, Index: i=%d; j=%0d \n", omp_get_thread_num(), i, j);
        }
    }

    printf("\n   Primer 3.4\n");
    #pragma omp parallel for collapse(2)
    for(int i=0; i<max; i++) {
        for(int j=0; j<max; j++) {
            printf("Thread: %d, Index: i=%d; j=%0d \n", omp_get_thread_num(), i, j);
        }
    }

    printf("\n   Primer 3.5\n");
    #pragma omp parallel for
    for(int i=0; i<max; i++) {
        #pragma omp parallel for
        for(int j=0; j<max; j++) {
            printf("Thread: %d, Index: i=%d; j=%0d \n", omp_get_thread_num(), i, j);
        }
    }

    return 0;
}
