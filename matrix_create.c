#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_MATRICES 4

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Please provide a matrix size\n");
        return 1;
    }

    int matrix_size = atoi(argv[1]);

    float (*matrices)[matrix_size][matrix_size] = (float (*)[matrix_size][matrix_size]) malloc(NUM_MATRICES * matrix_size * matrix_size * sizeof(float));

    srand(time(0));

    // Generate random values for all matrices
    for (int k = 0; k < NUM_MATRICES; k++) {
        for (int i = 0; i < matrix_size; i++) {
            for (int j = 0; j < matrix_size; j++) {
                matrices[k][i][j] = ((float)rand())/RAND_MAX;
            }
        }
    }

    // Save matrices to disk
    char *matrix_names[NUM_MATRICES] = {"A1", "B1", "A2", "B2"};
    for (int k = 0; k < NUM_MATRICES; k++) {
        char file_name[8];
        sprintf(file_name, "%s", matrix_names[k]);
        FILE *fp = fopen(file_name, "wb");
        fwrite(matrices[k], sizeof(float), matrix_size * matrix_size, fp);
        fclose(fp);
    }

    free(matrices);
    return 0;
}
