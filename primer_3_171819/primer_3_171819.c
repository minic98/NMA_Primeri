#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

double rnd(unsigned int *seed) {
    *seed = (1140671485 * (*seed) + 12820163) %(1 << 24);
    return ((double) (*seed)) / (1 << 24);
}

int main(int argc, char* argv[]) {
    int num_shots, num_hits, shot;

    printf("Unesite broj gadjanja: ");
    scanf("%d", &num_shots);

    // Primer 3.17
    {
        unsigned int *seeds = (unsigned int *)malloc(omp_get_max_threads() * sizeof(unsigned int));
        for(int thread=0; thread<omp_get_max_threads(); thread++)
            seeds[thread] = thread;

        num_hits = 0;
        #pragma omp parallel for reduction(+:num_hits)
        for(int shot=0; shot<num_shots; shot++) {
            int thread = omp_get_thread_num();
            double x = rnd(&seeds[thread]);
            double y = rnd(&seeds[thread]);
            if((x * x + y * y) <= 1) num_hits++;
        }
        double pi = 4.0 * (double)num_hits / (double)num_shots;
        printf("3.17 | Vrednost pi=%1.20f \n", pi);

        free(seeds);
    }
        
    // Primer 3.18
    {
        num_hits = 0;
        #pragma omp parallel
        {
        unsigned int seed = omp_get_thread_num();
        #pragma omp parallel for reduction(+:num_hits)
        for(int shot=0; shot<num_shots; shot++) {
            double x = rnd(&seed);
            double y = rnd(&seed);
            if((x * x + y * y) <= 1) num_hits++;
        }
        }
        double pi = 4.0 * (double)num_hits / (double)num_shots;
        printf("3.18 | Vrednost pi=%1.20f \n", pi);
    }

    // Primer 3.19
    {
        num_hits = 0;
        #pragma omp parallel reduction(+:num_hits)
        {
            unsigned int seed = omp_get_thread_num();
            int loc_shots = (num_shots / omp_get_num_threads()) + (num_shots % omp_get_num_threads() > omp_get_thread_num() ? 1 : 0);
            while(loc_shots-- > 0) {
                double x = rnd(&seed);
                double y = rnd(&seed);
                if((x * x + y * y) <= 1) num_hits++;
            }
        }
        double pi = 4.0 * (double)num_hits / (double)num_shots;
        printf("3.19 | Vrednost pi=%1.20f \n", pi);
    }

    return 0;
}