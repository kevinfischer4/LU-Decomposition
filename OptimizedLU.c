#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <xmmintrin.h> // Header for SSE-Instructions

void ludecompV2(size_t n, const float *A, float *L, float *U)
{
    if (n == 0)
    {
        return;
    }

    size_t buffersize = n * n * sizeof(float);
    float *Lbuffer = (float *)malloc(buffersize);
    float *Ubuffer = (float *)malloc(buffersize);

    // Initialization of L and U
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            L[i * n + j] = (i == j) ? 1.0f : 0.0f;
            U[i * n + j] = A[i * n + j];
        }
    }

    // If Matrix < 4x4, calculation without SIMD instructions
    if (n < 4)
    {
        for (size_t i = 0; i < n - 1; i++)
        {

            float temp = U[i * n + i];

            if (temp == 0)
            {
                temp = 1;
            }
            for (size_t j = i + 1; j < n; j++)
            {

                L[j * n + i] = U[j * n + i] / temp;

                for (size_t k = i; k < n; k++)
                {
                    U[j * n + k] -= L[j * n + i] * U[i * n + k];
                }
            }
        }
        free(Lbuffer);
        free(Ubuffer);

        return;
    }

    size_t simd_length = 4; // Size of SIMD-Register (128 Bit / 32 Bit per element)
    size_t simd_iterations = n / simd_length;

    float temp_vec;
    __m128 L_vec;
    __m128 U_row_vec;
    size_t h = 0;

    for (size_t i = 0; i < n - 1; i++)
    {
        if (U[i * n + i] == 0.0)
        {
            temp_vec = 1;
        }
        else
        {
            temp_vec = U[i * n + i];
        }

        // SSE-optimized calculation
        for (size_t j = i + 1; j < n; j++)
        {
            float helper = U[j * n + i] / temp_vec;
            L_vec = _mm_set1_ps(helper);
            h = i;

            for (size_t k = i; k < simd_iterations * simd_length && k <= (n - 3); k += simd_length)
            {
                U_row_vec = _mm_loadu_ps(U + i * n + k);

                _mm_storeu_ps(U + j * n + k, _mm_sub_ps(_mm_loadu_ps(U + j * n + k), _mm_mul_ps(L_vec, U_row_vec)));
                h = k + 4;
            }

            // Process remaining elements outside the SIMD length
            for (size_t k = h; k < n; k++)
            {
                U[j * n + k] -= helper * U[i * n + k];
            }
            // Save the updated vector in L
            L[j * n + i] = helper;
        }
    }

    free(Lbuffer);
    free(Ubuffer);
}
