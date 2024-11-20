#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[]) {
    if (argc < 4) {
        printf("Please provide matrix size, two matrix filenames\n");
        return 1;
    }

    int matrix_size = atoi(argv[1]);
    char *input_file1 = argv[2];
    char *input_file2 = argv[3];

    // Open the input files and check for errors
    FILE *fp1 = fopen(input_file1, "rb");
    if (fp1 == NULL) {
        printf("Error opening file %s\n", input_file1);
        return 1;
    }

    FILE *fp2 = fopen(input_file2, "rb");
    if (fp2 == NULL) {
        printf("Error opening file %s\n", input_file2);
        fclose(fp1);
        return 1;
    }

    // Allocate memory for the matrices
    float (*matrix1)[matrix_size] = (float (*)[matrix_size]) malloc(matrix_size * matrix_size * sizeof(float));
    float (*matrix2)[matrix_size] = (float (*)[matrix_size]) malloc(matrix_size * matrix_size * sizeof(float));
    float (*result)[matrix_size] = (float (*)[matrix_size]) malloc(matrix_size * matrix_size * sizeof(float));

    // Read the matrices from the input files
    size_t elements_read1 = fread(matrix1, sizeof(float), matrix_size * matrix_size, fp1);
    if(elements_read1!=matrix_size*matrix_size){
        printf("Error reading matrix1: number of elements read is not equal matrix size!\n");
        return 1;
    }

    size_t elements_read2 = fread(matrix2, sizeof(float), matrix_size * matrix_size, fp2);
    if(elements_read2!=matrix_size*matrix_size){
        printf("Error reading matrix2: number of elements read is not equal matrix size!\n");
        return 1;
    }

    // Initialize the result matrix to 0
    for (int i = 0; i < matrix_size; i++) {
        for (int j = 0; j < matrix_size; j++) {
            result[i][j] = 0.0;
        }
    }

    // Start timer
    double start = omp_get_wtime();

    // Matrix multiplication using OpenMP
    #pragma omp parallel for
    for (int i = 0; i < matrix_size; i++) {
        for (int j = 0; j < matrix_size; j++) {
            for (int k = 0; k < matrix_size; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    // Stop timer
    double end = omp_get_wtime();
    // Calculate multiplication time
    double elapsed_time = end - start;
    printf("Multiplication time: %.2fs\n", elapsed_time);

    // Close the input files
    fclose(fp1);
    fclose(fp2);

    // Create the output file name by concatenating the input file names
    char output_file[256];
    sprintf(output_file, "%s%s", input_file1, input_file2);

    // Open the output file and check for errors
    FILE *fp3 = fopen(output_file, "w");
    if (fp3 == NULL) {
        printf("Error opening file %s\n", output_file);
        return 1;
    }

    // Write the result matrix to the output file
    fwrite(result, sizeof(float), matrix_size * matrix_size, fp3);

    // Close the output file
    fclose(fp3);

    free(matrix1);
    free(matrix2);
    free(result);

    return 0;
}
