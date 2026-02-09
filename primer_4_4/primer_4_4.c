#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

// Helper comparison function for strings
int compareStrings(const char* a, const char* b) {
    return strcmp(a, b);
}

// Parallel Quicksort function from image
void par_qsort(char** data, int lo, int hi,
               int (*compare)(const char*, const char*)) {
    if (lo >= hi) return;
    int l = lo;
    int h = hi;
    // Pivot selection
    char* p = data[(hi + lo) / 2];
    
    while (l <= h) {
        while (compare(data[l], p) < 0) l++;
        while (compare(data[h], p) > 0) h--;
        if (l <= h) {
            char* tmp = data[l];
            data[l] = data[h];
            data[h] = tmp;
            l++;
            h--;
        }
    }
    
    // Task-based parallelism
    #pragma omp task final(h - lo < 1000)
    par_qsort(data, lo, h, compare);
    
    #pragma omp task final(hi - l < 1000)
    par_qsort(data, l, hi, compare);
}

// MAIN FUNCTION - Required for compiling
int main() {
    // Sample data to sort
    char* data[] = {"banana", "apple", "date", "cherry", "fig", "grape"};
    int n = sizeof(data) / sizeof(data[0]);
    
    printf("Before sorting:\n");
    for(int i = 0; i < n; i++) printf("%s ", data[i]);
    printf("\n");
    
    // Start parallel region
    #pragma omp parallel
    {
        // Single thread initiates the process
        #pragma omp single
        {
            par_qsort(data, 0, n - 1, compareStrings);
        }
    }
    
    printf("After sorting:\n");
    for(int i = 0; i < n; i++) printf("%s ", data[i]);
    printf("\n");
    
    return 0;
}