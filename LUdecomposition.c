#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void ludecomp(size_t n, const float *A, float *L, float *U)
{
    if (n == 0)
    {
        return;
    }

    // allocate buffer size for L and U , A will be given so we don't need to allocate
    size_t buffersize = n * n * sizeof(float);

    float *Lbuffer = (float *)malloc(buffersize);
    float *Ubuffer = (float *)malloc(buffersize);

    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            if (i == j)
            {
                L[i * n + j] = 1.0f;
                U[i * n + j] = A[i * n + j];
            }
            else
            {
                L[i * n + j] = 0.0f;
                U[i * n + j] = A[i * n + j];
            }
        }
    }

    // calculation of L and U
    for (size_t i = 0; i < n - 1; i++)
    {

        float temp = U[i * n + i];

        if (temp == 0)
        {
            temp = 1; // Prevent division by zero
        }

        for (size_t j = i + 1; j < n; j++)
        {

            // Calculating constant and placing it in L
            L[j * n + i] = U[j * n + i] / temp;

            // Calculation of the new values
            for (size_t k = i; k < n; k++)
            {
                U[j * n + k] -= L[j * n + i] * U[i * n + k];
            }
        }
    }
    // O(n^3): 3 inner loops

    free(Lbuffer);
    free(Ubuffer);
}
