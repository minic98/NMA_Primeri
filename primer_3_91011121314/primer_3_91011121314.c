#include <stdio.h>
#include <omp.h>

int main(int argc, char* argv[]) {
    int max, i;
    int sum = 0;
    double start_time, end_time;

    printf("Unestie maksimalnu vrednost: ");
    scanf("%d", &max);

    // 3.9/11 - sumiranje clih brojeva iz datog intervala koristeci jednu zajednicku promenljivu
    // POGRESNO
    sum = 0;
    start_time = omp_get_wtime();
    #pragma omp parallel for 
    for(i=1; i<=max; i++) {
        sum += i;
    }
    end_time = omp_get_wtime();
    printf("3.9/11 | Suma je: %0d; Potrebno vreme za izvresnje: %f \n", sum, end_time-start_time);

   
    // 3.10/12 - sumiranje clih brojeva iz datog intervala koristeci kriticnu sekciju
    // SPORO
    sum = 0;
    start_time = omp_get_wtime();
    #pragma omp parallel for 
    for(i=1; i<=max; i++) {
        #pragma omp critical
        sum += i;
    }
    end_time = omp_get_wtime();
    printf("3.10/12 | Suma je: %0d; Potrebno vreme za izvresnje: %f \n", sum, end_time-start_time);

    // 3.13 - sumiranje clih brojeva iz datog intervala koristeci pristup atomskoj promenljivoj
    // BRZE
    sum = 0;
    start_time = omp_get_wtime();
    #pragma omp parallel for 
    for(i=1; i<=max; i++) {
        #pragma omp atomic
        sum += i;
    }
    end_time = omp_get_wtime();
    printf("3.13 | Suma je: %0d; Potrebno vreme za izvresnje: %f \n", sum, end_time-start_time);

    // 3.14 - sumiranje clih brojeva iz datog intervala koristeci redukciju
    // BRZO
    sum = 0;
    start_time = omp_get_wtime();
    #pragma omp parallel for reduction(+:sum)
    for(i=1; i<=max; i++) {
        sum += i;
    }
    end_time = omp_get_wtime();
    printf("3.14 | Suma je: %0d; Potrebno vreme za izvresnje: %f \n", sum, end_time-start_time);

    return 0;
}