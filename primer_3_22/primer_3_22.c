#include <stdio.h>
#include <omp.h>

int main(int argc, char* argv[]) {
    int max, ts = 10;
    int sums[10];
    double start_time, end_time;

    printf("Unestie maksimalnu vrednost: ");
    scanf("%d", &max);
    if(max % ts != 0) return 1;

    start_time = omp_get_wtime();
    #pragma omp parallel
    {
        // int t = omp_get_max_threads();
        int t = omp_get_thread_num();
        int lo = (max / ts) * (t + 0) + 1;
        int hi = (max / ts) * (t + 1) + 0;
        sums[t] = 0;
        for(int i=lo; i<=hi; i++) {
            sums[t] += i;
        }
    }
    int sum = 0;
    for(int t=0; t<ts; t++) sum+=sums[t];
    end_time = omp_get_wtime();

    printf("3.22 | Suma je: %0d; Potrebno vreme za izvresnje: %f \n", sum, end_time-start_time);

    return 0;
}