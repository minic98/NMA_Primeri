#include <stdio.h>
#include <omp.h>

long fib(int n) {
    return (n<2 ? 1 : fib(n-1)+fib(n-2));
}

int main() {
    int n = 20;
    printf("Fibonacci sequence \n");

    #pragma omp parallel
    {
        int t = omp_get_thread_num();
        printf("Thread: %d | %ld \n", t, fib(n+t));
    }

    return 0;
}
