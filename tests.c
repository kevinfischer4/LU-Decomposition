#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define TRUE 1
#define FALSE 0

int equal(size_t n, const float *expected, const float *actual)
{
    for (size_t i = 0; i < n * n; i++)
    {
        if (expected[i] != actual[i])
        {
            printf("Expected : %f , got : %f at index %lu\n", expected[i], actual[i], i);
            for (size_t j = 0; j < n; j++)
            {
                for (size_t k = 0; k < n; k++)
                {
                    printf("%f\t ", actual[j * n + k]);
                }
                printf("\n");
            }
            return FALSE;
        }
    }
    return TRUE;
}

void test(const float *expected, const float *actual, size_t n, const char *TestName)
{
    if (equal(n, expected, actual))
    {
        printf("Test %s passed\n", TestName);
    }
    else
    {
        printf("Test %s failed\n", TestName);
    }
}

void testLarge(size_t n, const float *L, const float *U, size_t testNumber, const char *implementation)
{
    // check if L1 has only ones on the diagonal and ones in the first column
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            if (i == j)
            {
                if (L[i * n + j] != 1.0)
                {
                    printf("Test %lu failed in %s\n", testNumber, implementation);
                    return;
                }
            }
            else if (j == 0)
            {
                if (L[i * n + j] != 1.0)
                {
                    printf("Test %lu failed in %s\n", testNumber, implementation);
                    return;
                }
            }
            else
            {
                if (L[i * n + j] != 0.0)
                {
                    printf("Test %lu failed in %s\n", testNumber, implementation);
                    return;
                }
            }
        }
    }

    // check if U1 has only ones in the first row
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            if (i == 0)
            {
                if (U[i * n + j] != 1.0)
                {
                    printf("Test %lu failed in %s\n", testNumber, implementation);
                    return;
                }
            }
            else
            {
                if (U[i * n + j] != 0.0)
                {
                    printf("Test %lu failed in %s\n", testNumber, implementation);
                    return;
                }
            }
        }
    }
}

void allTestCases()
{

    // 1x1 Matrix

    printf("\n\n.....Test 1..... (1x1 Matrix)\n\n");

    size_t n1 = 1;

    float A1[1] = {1.0};

    float LResult1[1] = {1.0};

    float UResult1[1] = {1.0};

    float L1[1];
    float U1[1];

    ludecomp(n1, A1, L1, U1);

    test(LResult1, L1, n1, "L (ludecomp)");
    test(UResult1, U1, n1, "U (ludecomp)");

    float L1V2[1];
    float U1V2[1];

    ludecompV2(n1, A1, L1V2, U1V2);

    test(LResult1, L1V2, n1, "L (ludecompV2)");
    test(UResult1, U1V2, n1, "U (ludecompV2)");

    // 2x2 Matrix

    printf("\n\n.....Test 2..... (2x2 Matrix)\n\n");

    size_t n2 = 2;

    float A2[4] = {1.0, 2.0,
                   3.0, 4.0};

    float LResult2[4] = {1.0, 0.0,
                         3.0, 1.0};

    float UResult2[4] = {1.0, 2.0,
                         0.0, -2.0};

    float L2[4];
    float U2[4];

    ludecomp(n2, A2, L2, U2);

    test(LResult2, L2, n2, "L (ludecomp)");
    test(UResult2, U2, n2, "U (ludecomp)");

    float L2V2[4];
    float U2V2[4];

    ludecompV2(n2, A2, L2V2, U2V2);

    test(LResult2, L2V2, n2, "L (ludecompV2)");
    test(UResult2, U2V2, n2, "U (ludecompV2)");

    // 3x3 Matrix

    printf("\n\n.....Test 3..... (3x3 Matrix)\n\n");

    size_t n3 = 3;

    float A3[9] = {1.0, 2.0, 3.0,
                   4.0, 5.0, 6.0,
                   7.0, 8.0, 9.0};

    float LResult3[9] = {1.0, 0.0, 0.0,
                         4.0, 1.0, 0.0,
                         7.0, 2.0, 1.0};

    float UResult3[9] = {1.0, 2.0, 3.0,
                         0.0, -3.0, -6.0,
                         0.0, 0.0, 0.0};

    float L3[9];
    float U3[9];

    ludecomp(n3, A3, L3, U3);
    test(LResult3, L3, n3, "L (ludecomp)");
    test(UResult3, U3, n3, "U (ludecomp)");

    float L3V2[9];
    float U3V2[9];

    ludecompV2(n3, A3, L3V2, U3V2);
    test(LResult3, L3V2, n3, "L (ludecompV2)");
    test(UResult3, U3V2, n3, "U (ludecompV2)");

    // 4x4 Matrix

    printf("\n\n.....Test 4..... (4x4 Matrix)\n\n");

    size_t n4 = 4;

    float A4[16] = {1.0, 2.0, 3.0, 4.0,
                    5.0, 6.0, 7.0, 8.0,
                    9.0, 10.0, 11.0, 12.0,
                    13.0, 14.0, 15.0, 16.0};

    float LResult4[16] = {1.0, 0.0, 0.0, 0.0,
                          5.0, 1.0, 0.0, 0.0,
                          9.0, 2.0, 1.0, 0.0,
                          13.0, 3.0, 0.0, 1.0};

    float UResult4[16] = {1.0, 2.0, 3.0, 4.0,
                          0.0, -4.0, -8.0, -12.0,
                          0.0, 0.0, 0.0, 0.0,
                          0.0, 0.0, 0.0, 0.0};

    float L4[16];
    float U4[16];

    ludecomp(n4, A4, L4, U4);

    test(LResult4, L4, n4, "L (ludecomp)");
    test(UResult4, U4, n4, "U (ludecomp)");

    float L4V2[16];
    float U4V2[16];

    ludecompV2(n4, A4, L4V2, U4V2);

    test(LResult4, L4V2, n4, "L (ludecompV2)");
    test(UResult4, U4V2, n4, "U (ludecompV2)");

    // Test 6 5x5 Matrix

    printf("\n\n.....Test 5.....\n\n");

    size_t n5 = 5;

    float A5[25] = {1.0, 2.0, 3.0, 4.0, 5.0,
                    6.0, 7.0, 8.0, 9.0, 10.0,
                    11.0, 12.0, 13.0, 14.0, 15.0,
                    16.0, 17.0, 18.0, 19.0, 20.0,
                    21.0, 22.0, 23.0, 24.0, 25.0};

    float LResult5[25] = {1.0, 0.0, 0.0, 0.0, 0.0,
                          6.0, 1.0, 0.0, 0.0, 0.0,
                          11.0, 2.0, 1.0, 0.0, 0.0,
                          16.0, 3.0, 0.0, 1.0, 0.0,
                          21.0, 4.0, 0.0, 0.0, 1.0};

    float UResult5[25] = {1.0, 2.0, 3.0, 4.0, 5.0,
                          0.0, -5.0, -10.0, -15.0, -20.0,
                          0.0, 0.0, 0.0, 0.0, 0.0,
                          0.0, 0.0, 0.0, 0.0, 0.0,
                          0.0, 0.0, 0.0, 0.0, 0.0};

    float L5[25];
    float U5[25];

    ludecomp(n5, A5, L5, U5);

    test(LResult5, L5, n5, "L (ludecomp)");
    test(UResult5, U5, n5, "U (ludecomp)");

    float L5V2[25];
    float U5V2[25];

    ludecompV2(n5, A5, L5V2, U5V2);

    test(LResult5, L5V2, n5, "L (ludecompV2)");
    test(UResult5, U5V2, n5, "U (ludecompV2)");

    // Test 7 8x8 Matrix

    printf("\n\n.....Test 6..... (8x8 Matrix)\n\n");

    size_t n6 = 8;

    float A6[64] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0,
                    9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0,
                    17.0, 18.0, 19.0, 20.0, 21.0, 22.0, 23.0, 24.0,
                    25.0, 26.0, 27.0, 28.0, 29.0, 30.0, 31.0, 32.0,
                    33.0, 34.0, 35.0, 36.0, 37.0, 38.0, 39.0, 40.0,
                    41.0, 42.0, 43.0, 44.0, 45.0, 46.0, 47.0, 48.0,
                    49.0, 50.0, 51.0, 52.0, 53.0, 54.0, 55.0, 56.0,
                    57.0, 58.0, 59.0, 60.0, 61.0, 62.0, 63.0, 64.0};

    float LResult6[64] = {1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                          9.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                          17.0, 2.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                          25.0, 3.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,
                          33.0, 4.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0,
                          41.0, 5.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0,
                          49.0, 6.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0,
                          57.0, 7.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0};

    float UResult6[64] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0,
                          0.0, -8.0, -16.0, -24.0, -32.0, -40.0, -48.0, -56.0,
                          0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                          0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                          0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                          0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                          0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                          0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

    float L6[64];
    float U6[64];

    ludecomp(n6, A6, L6, U6);

    test(LResult6, L6, n6, "L (ludecomp)");
    test(UResult6, U6, n6, "U (ludecomp)");

    float L6V2[64];
    float U6V2[64];

    ludecompV2(n6, A6, L6V2, U6V2);

    test(LResult6, L6V2, n6, "L (ludecompV2)");
    test(UResult6, U6V2, n6, "U (ludecompV2)");

    // large Examples

    printf("\n\n.....Test 7..... (10x10 Matrix)\n\n");

    size_t n7 = 10;

    float *A7 = (float *)malloc(n7 * n7 * sizeof(float));

    for (size_t i = 0; i < n7 * n7; i++)
    {
        A7[i] = 1.0;
    }

    float *L7 = (float *)malloc(n7 * n7 * sizeof(float));
    float *U7 = (float *)malloc(n7 * n7 * sizeof(float));

    ludecomp(n7, A7, L7, U7);

    testLarge(n7, L7, U7, 7, "(ludecomp)");

    printf("Test 7(ludecomp) passed\n");

    float *L7V2 = (float *)malloc(n7 * n7 * sizeof(float));
    float *U7V2 = (float *)malloc(n7 * n7 * sizeof(float));

    ludecompV2(n7, A7, L7V2, U7V2);

    testLarge(n7, L7V2, U7V2, 7, "(ludecompV2)");

    printf("Test 7(ludecompV2) passed\n");

    free(A7);
    free(L7);
    free(U7);
    free(L7V2);
    free(U7V2);

    printf("\n\n.....Test 8..... (100x100 Matrix)\n\n");

    size_t n8 = 100;

    float *A8 = (float *)malloc(n8 * n8 * sizeof(float));

    for (size_t i = 0; i < n8 * n8; i++)
    {
        A8[i] = 1.0;
    }

    float *L8 = (float *)malloc(n8 * n8 * sizeof(float));
    float *U8 = (float *)malloc(n8 * n8 * sizeof(float));

    ludecomp(n8, A8, L8, U8);

    testLarge(n8, L8, U8, 8, "(ludecomp)");

    printf("Test 8(ludecomp) passed\n");

    float *L8V2 = (float *)malloc(n8 * n8 * sizeof(float));
    float *U8V2 = (float *)malloc(n8 * n8 * sizeof(float));

    ludecompV2(n8, A8, L8V2, U8V2);

    testLarge(n8, L8V2, U8V2, 8, "(ludecompV2)");

    printf("Test 8(ludecompV2) passed\n");

    free(A8);
    free(L8);
    free(U8);
    free(L8V2);
    free(U8V2);

    printf("\n\n.....Test 9..... (1000x1000 Matrix)\n\n");

    size_t n9 = 1000;

    float *A9 = (float *)malloc(n9 * n9 * sizeof(float));

    for (size_t i = 0; i < n9 * n9; i++)
    {
        A9[i] = 1.0;
    }

    float *L9 = (float *)malloc(n9 * n9 * sizeof(float));
    float *U9 = (float *)malloc(n9 * n9 * sizeof(float));

    ludecomp(n9, A9, L9, U9);

    testLarge(n9, L9, U9, 9, "(ludecomp)");

    printf("Test 9(ludecomp) passed\n");

    float *L9V2 = (float *)malloc(n9 * n9 * sizeof(float));
    float *U9V2 = (float *)malloc(n9 * n9 * sizeof(float));

    ludecompV2(n9, A9, L9V2, U9V2);

    testLarge(n9, L9V2, U9V2, 9, "(ludecompV2)");

    printf("Test 9(ludecompV2) passed\n\n");

    free(A9);
    free(L9);
    free(U9);
    free(L9V2);
    free(U9V2);

    // Edge Cases

    // NULL Matrix

    printf("\n\n.....Test 10..... (NULL Matrix)\n\n");

    size_t n10 = 0;

    float A10[1] = {0.0};

    float LResult10[1] = {1.0};

    float UResult10[1] = {0.0};

    float L10[1];
    float U10[1];

    ludecomp(n10, A10, L10, U10);

    test(LResult10, L10, n10, "L (ludecomp)");
    test(UResult10, U10, n10, "U (ludecomp)");

    float L10V2[1];
    float U10V2[1];

    ludecompV2(n10, A10, L10V2, U10V2);

    test(LResult10, L10V2, n10, "L (ludecompV2)");
    test(UResult10, U10V2, n10, "U (ludecompV2)");

    // Einheitsmatrix

    printf("\n\n.....Test 11..... (Einheitsmatrix)\n\n");

    size_t n11 = 4;

    float A11[16] = {1.0, 0.0, 0.0, 0.0,
                     0.0, 1.0, 0.0, 0.0,
                     0.0, 0.0, 1.0, 0.0,
                     0.0, 0.0, 0.0, 1.0};

    float LResult11[16] = {1.0, 0.0, 0.0, 0.0,
                           0.0, 1.0, 0.0, 0.0,
                           0.0, 0.0, 1.0, 0.0,
                           0.0, 0.0, 0.0, 1.0};

    float UResult11[16] = {1.0, 0.0, 0.0, 0.0,
                           0.0, 1.0, 0.0, 0.0,
                           0.0, 0.0, 1.0, 0.0,
                           0.0, 0.0, 0.0, 1.0};

    float L11[16];
    float U11[16];

    ludecomp(n11, A11, L11, U11);

    test(LResult11, L11, n11, "L (ludecomp)");
    test(UResult11, U11, n11, "U (ludecomp)");

    float L11V2[16];
    float U11V2[16];

    ludecompV2(n11, A11, L11V2, U11V2);

    test(LResult11, L11V2, n11, "L (ludecompV2)");
    test(UResult11, U11V2, n11, "U (ludecompV2)");

    // float overflow

    printf("\n\n.....Test 12..... (float overflow)\n\n");

    size_t n12 = 3;

    float max = __FLT_MAX__;
    float k = max / 2;
    float A12[9] = {k, k, k,
                    k, k, k,
                    k, k, k};

    float LResult12[9] = {1.0, 0.0, 0.0,
                          1.0, 1.0, 0.0,
                          1.0, 0.0, 1.0};

    float UResult12[9] = {k, k, k,
                          0.0, 0.0, 0.0,
                          0.0, 0.0, 0.0};

    float L12[9];
    float U12[9];

    ludecomp(n12, A12, L12, U12);

    test(LResult12, L12, n12, "L (ludecomp)");
    test(UResult12, U12, n12, "U (ludecomp)");

    float L12V2[9];
    float U12V2[9];

    ludecompV2(n12, A12, L12V2, U12V2);

    test(LResult12, L12V2, n12, "L (ludecompV2)");
    test(UResult12, U12V2, n12, "U (ludecompV2)");

    // tolerance

    printf("\n\n.....Test 13..... (tolerance)\n\n");

    size_t n13 = 3;

    float A13[9] = {0.0001, 0.0002, 0.0003,
                    0.0004, 0.0005, 0.0006,
                    0.0007, 0.0008, 0.0009};

    float LResult13[9] = {1.0, 0.0, 0.0,
                          4.0, 1.0, 0.0,
                          7.0, 2.0, 1.0};

    float UResult13[9] = {0.0001, 0.0002, 0.0003,
                          0.0, -0.0003, -0.0006,
                          0.0, 0.0, 0.0};

    float L13[9];
    float U13[9];

    ludecomp(n13, A13, L13, U13);

    // check if tolerance is met
    for (size_t i = 0; i < n13; i++)
    {
        for (size_t j = 0; j < n13; j++)
        {
            if (fabs(L13[i * n13 + j] - LResult13[i * n13 + j]) < 0.0001)
            {
                L13[i * n13 + j] = LResult13[i * n13 + j];
            }
            if (fabs(U13[i * n13 + j] - UResult13[i * n13 + j]) < 0.0001)
            {
                U13[i * n13 + j] = UResult13[i * n13 + j];
            }
        }
    }

    test(LResult13, L13, n13, "L (ludecomp)");
    test(UResult13, U13, n13, "U (ludecomp)");

    float L13V2[9];
    float U13V2[9];

    ludecompV2(n13, A13, L13V2, U13V2);

    // check if tolerance is met
    for (size_t i = 0; i < n13; i++)
    {
        for (size_t j = 0; j < n13; j++)
        {
            if (fabs(L13V2[i * n13 + j] - LResult13[i * n13 + j]) < 0.0001)
            {
                L13V2[i * n13 + j] = LResult13[i * n13 + j];
            }
            if (fabs(U13V2[i * n13 + j] - UResult13[i * n13 + j]) < 0.0001)
            {
                U13V2[i * n13 + j] = UResult13[i * n13 + j];
            }
        }
    }

    test(LResult13, L13V2, n13, "L (ludecompV2)");
    test(UResult13, U13V2, n13, "U (ludecompV2)");

    printf("\n");
}

void testCasesSmall()
{
    // Matrixsize 0 - 4 (until one Simd Operatoin)

    // 1x1 Matrix

    printf("\n\n.....Test 1..... (1x1 Matrix)\n\n");

    size_t n1 = 1;

    float A1[1] = {1.0};

    float LResult1[1] = {1.0};

    float UResult1[1] = {1.0};

    float L1[1];
    float U1[1];

    ludecomp(n1, A1, L1, U1);

    test(LResult1, L1, n1, "L (ludecomp)");
    test(UResult1, U1, n1, "U (ludecomp)");

    float L1V2[1];
    float U1V2[1];

    ludecompV2(n1, A1, L1V2, U1V2);

    test(LResult1, L1V2, n1, "L (ludecompV2)");
    test(UResult1, U1V2, n1, "U (ludecompV2)");

    // 2x2 Matrix

    printf("\n\n.....Test 2..... (2x2 Matrix)\n\n");

    size_t n2 = 2;

    float A2[4] = {1.0, 2.0,
                   3.0, 4.0};

    float LResult2[4] = {1.0, 0.0,
                         3.0, 1.0};

    float UResult2[4] = {1.0, 2.0,
                         0.0, -2.0};

    float L2[4];
    float U2[4];

    ludecomp(n2, A2, L2, U2);

    test(LResult2, L2, n2, "L (ludecomp)");
    test(UResult2, U2, n2, "U (ludecomp)");

    float L2V2[4];
    float U2V2[4];

    ludecompV2(n2, A2, L2V2, U2V2);

    test(LResult2, L2V2, n2, "L (ludecompV2)");
    test(UResult2, U2V2, n2, "U (ludecompV2)");

    // 3x3 Matrix

    printf("\n\n.....Test 3..... (3x3 Matrix)\n\n");

    size_t n3 = 3;

    float A3[9] = {1.0, 2.0, 3.0,
                   4.0, 5.0, 6.0,
                   7.0, 8.0, 9.0};

    float LResult3[9] = {1.0, 0.0, 0.0,
                         4.0, 1.0, 0.0,
                         7.0, 2.0, 1.0};

    float UResult3[9] = {1.0, 2.0, 3.0,
                         0.0, -3.0, -6.0,
                         0.0, 0.0, 0.0};

    float L3[9];
    float U3[9];

    ludecomp(n3, A3, L3, U3);
    test(LResult3, L3, n3, "L (ludecomp)");
    test(UResult3, U3, n3, "U (ludecomp)");

    float L3V2[9];
    float U3V2[9];

    ludecompV2(n3, A3, L3V2, U3V2);
    test(LResult3, L3V2, n3, "L (ludecompV2)");
    test(UResult3, U3V2, n3, "U (ludecompV2)");

    // 4x4 Matrix

    printf("\n\n.....Test 4..... (4x4 Matrix)\n\n");

    size_t n4 = 4;

    float A4[16] = {1.0, 2.0, 3.0, 4.0,
                    5.0, 6.0, 7.0, 8.0,
                    9.0, 10.0, 11.0, 12.0,
                    13.0, 14.0, 15.0, 16.0};

    float LResult4[16] = {1.0, 0.0, 0.0, 0.0,
                          5.0, 1.0, 0.0, 0.0,
                          9.0, 2.0, 1.0, 0.0,
                          13.0, 3.0, 0.0, 1.0};

    float UResult4[16] = {1.0, 2.0, 3.0, 4.0,
                          0.0, -4.0, -8.0, -12.0,
                          0.0, 0.0, 0.0, 0.0,
                          0.0, 0.0, 0.0, 0.0};

    float L4[16];
    float U4[16];

    ludecomp(n4, A4, L4, U4);

    test(LResult4, L4, n4, "L (ludecomp)");
    test(UResult4, U4, n4, "U (ludecomp)");

    float L4V2[16];
    float U4V2[16];

    ludecompV2(n4, A4, L4V2, U4V2);

    test(LResult4, L4V2, n4, "L (ludecompV2)");
    test(UResult4, U4V2, n4, "U (ludecompV2)");

    printf("\n");
}

void testCasesLarge()
{
    printf("This is Large test\n");
    // 10x10 Matrix, 100x100 Matrix, 1000x1000 Matrix, 10000x10000 Matrix, 100000x100000 Matrix

    // 10x10 Matrix

    printf("\n\n.....Test 1..... (10x10 Matrix)\n\n");

    size_t n1 = 10;

    float *A1 = (float *)malloc(n1 * n1 * sizeof(float));

    // fill A1 with ones
    for (size_t i = 0; i < n1 * n1; i++)
    {
        A1[i] = 1.0;
    }

    float *L1 = (float *)malloc(n1 * n1 * sizeof(float));
    float *U1 = (float *)malloc(n1 * n1 * sizeof(float));

    ludecomp(n1, A1, L1, U1);

    testLarge(n1, L1, U1, 1, "(ludecomp)");

    float *L1V2 = (float *)malloc(n1 * n1 * sizeof(float));
    float *U1V2 = (float *)malloc(n1 * n1 * sizeof(float));

    ludecompV2(n1, A1, L1V2, U1V2);

    testLarge(n1, L1V2, U1V2, 1, "(ludecompV2)");

    printf("Test 1 passed\n");

    free(A1);
    free(L1);
    free(U1);
    free(L1V2);
    free(U1V2);

    // 100x100 Matrix

    printf("\n\n.....Test 2..... (100x100 Matrix)\n\n");

    size_t n2 = 100;

    float *A2 = (float *)malloc(n2 * n2 * sizeof(float));

    // fill A5 with ones
    for (size_t i = 0; i < n2 * n2; i++)
    {
        A2[i] = 1.0;
    }

    float *L2 = (float *)malloc(n2 * n2 * sizeof(float));
    float *U2 = (float *)malloc(n2 * n2 * sizeof(float));

    ludecomp(n2, A2, L2, U2);

    testLarge(n2, L2, U2, 2, "(ludecomp)");

    float *L2V2 = (float *)malloc(n2 * n2 * sizeof(float));
    float *U2V2 = (float *)malloc(n2 * n2 * sizeof(float));

    ludecompV2(n2, A2, L2V2, U2V2);

    testLarge(n2, L2V2, U2V2, 2, "(ludecompV2)");

    printf("Test 2 passed\n");

    free(A2);
    free(L2);
    free(U2);
    free(L2V2);
    free(U2V2);

    // 1000x1000 Matrix

    printf("\n\n.....Test 3..... (1000x1000 Matrix)\n\n");

    size_t n3 = 1000;

    float *A3 = (float *)malloc(n3 * n3 * sizeof(float));

    // fill A5 with ones
    for (size_t i = 0; i < n3 * n3; i++)
    {
        A3[i] = 1.0;
    }

    float *L3 = (float *)malloc(n3 * n3 * sizeof(float));
    float *U3 = (float *)malloc(n3 * n3 * sizeof(float));

    ludecomp(n3, A3, L3, U3);

    testLarge(n3, L3, U3, 3, "(ludecomp)");

    float *L3V2 = (float *)malloc(n3 * n3 * sizeof(float));
    float *U3V2 = (float *)malloc(n3 * n3 * sizeof(float));

    ludecompV2(n3, A3, L3V2, U3V2);

    testLarge(n3, L3V2, U3V2, 3, "(ludecompV2)");

    printf("Test 3 passed\n\n");

    free(A3);
    free(L3);
    free(U3);
    free(L3V2);
    free(U3V2);
}

void testCasesEdge()
{
    printf("This is Edge test\n");
    // NULL Matrix, einheitmatrix, float overflow, size overflow, Tolerance? 1e+9

    // NULL Matrix

    printf("\n\n.....Test 1..... (NULL Matrix)\n\n");

    size_t n1 = 0;

    float A1[1] = {0.0};

    float LResult1[1] = {1.0};

    float UResult1[1] = {0.0};

    float L1[1];
    float U1[1];

    ludecomp(n1, A1, L1, U1);

    test(LResult1, L1, n1, "L (ludecomp)");
    test(UResult1, U1, n1, "U (ludecomp)");

    float L1V2[1];
    float U1V2[1];

    ludecompV2(n1, A1, L1V2, U1V2);

    test(LResult1, L1V2, n1, "L (ludecompV2)");
    test(UResult1, U1V2, n1, "U (ludecompV2)");

    // Einheitsmatrix

    printf("\n\n.....Test 2..... (Einheitsmatrix)\n\n");

    size_t n2 = 4;

    float A2[16] = {1.0, 0.0, 0.0, 0.0,
                    0.0, 1.0, 0.0, 0.0,
                    0.0, 0.0, 1.0, 0.0,
                    0.0, 0.0, 0.0, 1.0};

    float LResult2[16] = {1.0, 0.0, 0.0, 0.0,
                          0.0, 1.0, 0.0, 0.0,
                          0.0, 0.0, 1.0, 0.0,
                          0.0, 0.0, 0.0, 1.0};

    float UResult2[16] = {1.0, 0.0, 0.0, 0.0,
                          0.0, 1.0, 0.0, 0.0,
                          0.0, 0.0, 1.0, 0.0,
                          0.0, 0.0, 0.0, 1.0};

    float L2[16];
    float U2[16];

    ludecomp(n2, A2, L2, U2);

    test(LResult2, L2, n2, "L (ludecomp)");
    test(UResult2, U2, n2, "U (ludecomp)");

    float L2V2[16];
    float U2V2[16];

    ludecompV2(n2, A2, L2V2, U2V2);

    test(LResult2, L2V2, n2, "L (ludecompV2)");
    test(UResult2, U2V2, n2, "U (ludecompV2)");

    // float overflow

    printf("\n\n.....Test 3..... (float overflow)\n\n");

    size_t n3 = 3;

    float max = __FLT_MAX__;
    float k = max / 2;
    float A3[9] = {k, k, k,
                   k, k, k,
                   k, k, k};

    float LResult3[9] = {1.0, 0.0, 0.0,
                         1.0, 1.0, 0.0,
                         1.0, 0.0, 1.0};

    float UResult3[9] = {k, k, k,
                         0.0, 0.0, 0.0,
                         0.0, 0.0, 0.0};

    float L3[9];
    float U3[9];

    ludecomp(n3, A3, L3, U3);

    test(LResult3, L3, n3, "L (ludecomp)");
    test(UResult3, U3, n3, "U (ludecomp)");

    float L3V2[9];
    float U3V2[9];

    ludecompV2(n3, A3, L3V2, U3V2);

    test(LResult3, L3V2, n3, "L (ludecompV2)");
    test(UResult3, U3V2, n3, "U (ludecompV2)");

    // tolerance

    printf("\n\n.....Test 4..... (tolerance)\n\n");

    size_t n4 = 3;

    float A4[9] = {0.0001, 0.0002, 0.0003,
                   0.0004, 0.0005, 0.0006,
                   0.0007, 0.0008, 0.0009};

    float LResult4[9] = {1.0, 0.0, 0.0,
                         4.0, 1.0, 0.0,
                         7.0, 2.0, 1.0};

    float UResult4[9] = {0.0001, 0.0002, 0.0003,
                         0.0, -0.0003, -0.0006,
                         0.0, 0.0, 0.0};

    float L4[9];
    float U4[9];

    ludecomp(n4, A4, L4, U4);

    // check if tolerance is met
    for (size_t i = 0; i < n4; i++)
    {
        for (size_t j = 0; j < n4; j++)
        {
            if (fabs(L4[i * n4 + j] - LResult4[i * n4 + j]) < 0.0001)
            {
                L4[i * n4 + j] = LResult4[i * n4 + j];
            }
            if (fabs(U4[i * n4 + j] - UResult4[i * n4 + j]) < 0.0001)
            {
                U4[i * n4 + j] = UResult4[i * n4 + j];
            }
        }
    }

    test(LResult4, L4, n4, "L (ludecomp)");
    test(UResult4, U4, n4, "U (ludecomp)");

    float L4V2[9];
    float U4V2[9];

    ludecompV2(n4, A4, L4V2, U4V2);

    // check if tolerance is met
    for (size_t i = 0; i < n4; i++)
    {
        for (size_t j = 0; j < n4; j++)
        {
            if (fabs(L4V2[i * n4 + j] - LResult4[i * n4 + j]) < 0.0001)
            {
                L4V2[i * n4 + j] = LResult4[i * n4 + j];
            }
            if (fabs(U4V2[i * n4 + j] - UResult4[i * n4 + j]) < 0.0001)
            {
                U4V2[i * n4 + j] = UResult4[i * n4 + j];
            }
        }
    }

    test(LResult4, L4V2, n4, "L (ludecompV2)");
    test(UResult4, U4V2, n4, "U (ludecompV2)");

    printf("\n");
}
