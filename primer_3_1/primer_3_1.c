#include <stdio.h>
#include <omp.h>

// Paralelizacija petlji

int main(int argc, char* argv[]) {
    int max;

    printf("Unesite maksimalnu vrednost: ");
    scanf("%d", &max);

        #pragma omp parallel for
        for(int i=0; i<max; i++) {
            printf("Thread: %d, Index: %d \n", omp_get_thread_num(), i);
        }

    return 0;
}
