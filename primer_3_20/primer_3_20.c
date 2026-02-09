#include <stdio.h>
#include <unistd.h>
#include <omp.h>

int main(int argc, char* argv[]) {
    int max, i;
    long int sum = 0;
    double start_time, end_time;

    printf("Unestie maksimalnu vrednost: ");
    scanf("%d", &max);

    {
        // Example without schedule clause
        sum = 0;
        start_time = omp_get_wtime();
        omp_set_num_threads(4);
        #pragma omp parallel for reduction(+:sum)
        for(i=1; i<=max; i++) {
            printf("Thread: %0d; Index i: %0d; \n", omp_get_thread_num(), i);
            sleep(i<4 ? (i+1) : 1); //Sleep for seconds
            sum += i;
        }
        end_time = omp_get_wtime();
        printf("Suma je: %0ld; Potrebno vreme za izvresnje: %f \n", sum, end_time-start_time);
    }
    printf("\n Demonstracija primera sa schedule kaluzulom \n");
    {
        // 3.20 - sumiranje clih brojeva iz datog intervala koristeci redukciju
        // Kad se koristi runtime onda se iz shell-a cita: 
        // OMP_SCHEDULE="tip[,chunk_size]"
        // # Postavlja schedule tip za petlje sa schedule(runtime)
        // # Primer: export OMP_SCHEDULE="dynamic,4"
        sum = 0;
        start_time = omp_get_wtime();
        omp_set_num_threads(4);
        #pragma omp parallel for reduction(+:sum) schedule(runtime)
        for(i=1; i<=max; i++) {
            printf("Thread: %0d; Index i: %0d; \n", omp_get_thread_num(), i);
            sleep(i<4 ? (i+1) : 1); //Sleep for seconds
            sum += i;
        }
        end_time = omp_get_wtime();
        printf("Suma je: %0ld; Potrebno vreme za izvresnje: %f \n", sum, end_time-start_time);
    }
    return 0;
}