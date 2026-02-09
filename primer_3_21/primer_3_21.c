#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <omp.h>

int main(int argc, char* argv[]) {
    const int i_size = 800; // Width
    const int j_size = 600; // Height
    const double min_re = -2.0;
    const double max_re = 1.0;
    const double min_im = -1.2;
    const double max_im = 1.2;
    const int max_iters = 1000;

    double start_time, end_time;

    // Calculate step sizes
    double d_re = (max_re - min_re) / i_size;
    double d_im = (max_im - min_im) / j_size;

    // Allocate memory for a 2D array (pixel values)
    int** picture = (int**)malloc(i_size * sizeof(int*));
    for (int i = 0; i < i_size; i++) {
        picture[i] = (int*)malloc(j_size * sizeof(int));
    }

    start_time = omp_get_wtime();
    #pragma omp parallel for collapse(2) schedule(dynamic,100)
    for(int i=0; i<i_size; i++) {
        for(int j=0; j<j_size; j++) {
            double c_re = min_re + i * d_re;
            double c_im = min_im + j * d_im;

            double z_re = 0.0;
            double z_im = 0.0;

            int iters = 0;
            while((z_re * z_re + z_im * z_im <= 4.0) && (iters < max_iters)) {
                double new_z_re = z_re * z_re - z_im * z_im + c_re;
                double new_z_im = 2 * z_re * z_im + c_im;
                z_re = new_z_re;
                z_im = new_z_im;
                iters++;
            }
            picture[i][j] = iters;
        }
    }
    end_time = omp_get_wtime();
    printf("primer 3.21 | Mandelbrot calculation complete.\n");
    printf("Potrebno vreme za izvresnje: %f \n", end_time-start_time);

    // Print Mandelbrot picture to file
    FILE *file = fopen("mandelbrot.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    char gradient[] = " .:-=+*#%@";
    int grad_len = 10;

    for(int j=0; j<j_size; j++) {
        for(int i=0; i<i_size; i++) {
            int iters = picture[i][j];
            if (iters == max_iters) {
                fprintf(file, "@"); // Write to file
            } else {
                int char_index = (iters * (grad_len - 1)) / max_iters;
                fprintf(file, "%c", gradient[char_index]); // Write to file
            }
        }
        fprintf(file, "\n"); // Write newline to file
    }

    fclose(file);
    printf("File saved as mandelbrot.txt\n");
    

    // Clean up memory
    for (int i = 0; i < i_size; i++) free(picture[i]);
    free(picture);

    return 0;
}