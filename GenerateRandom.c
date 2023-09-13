#include <stdio.h>
#include <stdlib.h>

void generate_random_matrix(size_t n)
{

    float *A = (float *)malloc(n * n * sizeof(float));

    // generating random numbers
    for (size_t i = 0; i < n * n; i++)
    {
        A[i] = (float)(rand() % 1000) + 1;
    }

    FILE *file = fopen("random.txt", "w+");
    // check for invalid file
    if (file == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    // write matrix to file in this format: [1,2,3] [4,5,6] [7,8,9]
    for (size_t i = 0; i < n; i++)
    {
        fprintf(file, "[");
        for (size_t j = 0; j < n; j++)
        {
            fprintf(file, "%f", A[i * n + j]);
            if (j < n - 1)
            {
                fprintf(file, ",\t\t\t");
            }
        }
        fprintf(file, "]\n");
    }

    fclose(file);
    free(A);
}
