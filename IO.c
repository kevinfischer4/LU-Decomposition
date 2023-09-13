#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include "LUdecomposition.c"
#include "OptimizedLU.c"
#include "tests.c"
#include "GenerateRandom.c"
#include <time.h>
#include <math.h>
#define BILLION 1000000000.0

void usage()
{
    // Instruction output and examples
    printf("Anleitung:\n");
    printf("-V<Zahl>         Die Implementierung, die verwendet werden soll.\n");
    printf("-B<Zahl>         Falls gesetzt, wird die Laufzeit der angegebenen Implementierung gemessen und ausgegeben.\n");
    printf("<Dateiname>      Positional Argument an Stelle 1: Datei, welche die Matrix A enthält.\n");
    printf("-r<Zahl>         Das Rahmenprogramm generiert eine zufällige Matrix einer vorgegebenen Größe und speichert sie als Datei ab.\n");
    printf("-o<Dateiname>    Ausgabedatei für die berechnete bzw. generierte Matrix.\n");
    printf("-t<Zahl>         Testet die Implementierung mit den ausgewählten Tests.\n");
    printf("-h               Eine Beschreibung aller Optionen des Programms und Verwendungsbeispiele werden ausgegeben und das Programm danach beendet.\n");
    printf("--help           Eine Beschreibung aller Optionen des Programms und Verwendungsbeispiele werden ausgegeben und das Programm danach beendet.\n");
    printf("Beispiel: ./main matrix.txt -V0 -B100 -r10 -o\"output.txt\" -t1\n");
    printf("Hinweis: Im positionalen Argument für die Eingabedatei muss immer eine valide Matrix vorhanden sein, welche auch nicht leer sein darf.\n\n \
            Format: \t[a11,\\ta12,\\ta13,...]\n   \
                    \t[a21,\\ta22,\\ta23,...]\n    \
                    [a31,\\ta32,\\ta33,...]\n    \
                    [..., ..., ..., ...]\n    \
    ");
}

void test_usage()
{
    // Instruction output and examples
    printf("Anleitung:\n");
    printf("Bitte geben Sie eine Zahl zwischen 0 und 3 an, um verschiedene Testsätze auszuführen.\n");
    printf("0: Testet die Implementierung mit allen Tests.\n");
    printf("1: Testet die Implementierung mit kleinen Matrizen.\n");
    printf("2: Testet die Implementierung mit großen Matrizen.\n");
    printf("3: Testet die Implementierung mit Sonderfällen.\n");
    printf("Beispiel: ./main -t1\n");
}

<<<<<<< HEAD
// load matrix from file and return the pointer to the matrix
float *load_matrix(const char *filename)
{
    // open file
    FILE *file = fopen(filename, "r");
    // check for invalid file
    if (file == NULL)
    {
        printf("Load_matrix_Error opening file!\n");
        exit(EXIT_FAILURE);
    }
=======
// load matrix from file and return the pointer to the matrix
float *load_matrix(const char *filename)
{

    // open file
    FILE *file = fopen(filename, "r");
    // check for invalid file
    if (file == NULL)
    {
        printf("Load_matrix_Error opening file : \"%s\"!\n", filename);
        exit(EXIT_FAILURE);
    }
>>>>>>> refs/remotes/origin/master

    // get size of matrix
    size_t n = 0;
    char c;
    while ((c = fgetc(file)) != EOF)
    {
        if (c == '[')
        {
            n++;
        }
    }

    // allocate memory for matrix
    float *A = (float *)malloc(n * n * sizeof(float));

    // reset file pointer to beginning of file
    fseek(file, 0, SEEK_SET);

    // read matrix from file
    for (size_t i = 0; i < n; i++)
    {
        // skip '['
        fgetc(file);
        for (size_t j = 0; j < n; j++)
        {
            int temp = fscanf(file, "%f", &A[i * n + j]);
            if (temp == EOF)
            {
                break;
            }
            // skip ',' and '\t'
            fgetc(file);
            fgetc(file);
        }
        // skip ']'
        fgetc(file);
        // skip '\n'
        fgetc(file);
    }
    fclose(file);
    return A;
}

// save matrix to file
void save_matrix(const char *filename, float *A, size_t n)
{

<<<<<<< HEAD
    // copy matrix to file
    FILE *file = fopen(filename, "w+");
    // check for invalid file
    if (file == NULL)
    {
        printf("Save_matrix_error opening file!\n");
=======
    // copy matrix to file
    FILE *file = fopen(filename, "w+");
    // check for invalid file
    if (file == NULL)
    {
        printf("Save_matrix_error opening file: \"%s\"!\n", filename);
>>>>>>> refs/remotes/origin/master
        exit(EXIT_FAILURE);
    }

    fprintf(file, "Matrix A:\n");
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
}

void save_output_matrix(const char *filename, const float *L, const float *U, size_t n)
{
    // copy matrix to file
    FILE *file = fopen(filename, "w+");
    // check for invalid file
    if (file == NULL)
    {
        printf("Save_output_matrix_error opening file: \"%s\"!\n", filename);
        exit(EXIT_FAILURE);
    }

    fprintf(file, "Matrix L:\n");
    for (size_t i = 0; i < n; i++)
    {
        fprintf(file, "[\t");
        for (size_t j = 0; j < n; j++)
        {
            fprintf(file, "%f\t\t\t", L[i * n + j]);
        }
        fprintf(file, "]\n");
    }

    fprintf(file, "\nMatrix U:\n");

    for (size_t i = 0; i < n; i++)
    {
        fprintf(file, "[\t");
        for (size_t j = 0; j < n; j++)
        {
            fprintf(file, "%f\t\t\t", U[i * n + j]);
        }
        fprintf(file, "]\n");
    }

    fclose(file);
}

void save_input_matrix(const char *filename, const char *matrix)
{
    FILE *file = fopen(filename, "w+");
    // check for invalid file
    if (file == NULL)
    {
        printf("Save_input_matrix_error opening file: \"%s\"!\n", filename);
        exit(EXIT_FAILURE);
    }

    fprintf(file, "Matrix A:\n");
    for (size_t i = 0; i < strlen(matrix); i++)
    {
        if (matrix[i] == '[')
        {
            fprintf(file, "[");
        }
        else if (matrix[i] == ']')
        {
            fprintf(file, "]\n");
        }
        else if (matrix[i] == ',')
        {
            fprintf(file, ",\t\t\t");
        }
        else
        {
            fprintf(file, "%c", matrix[i]);
        }
    }
    fclose(file);
}

double benchmarkEXE(int repeats, float *A, size_t n, int implementation)
{
    if (implementation < 0 || implementation > 1)
    {
        printf("Invalid implementation number %d\n", implementation);
        exit(EXIT_FAILURE);
    }

    struct timespec start, end;
    double time_spent;
    if (implementation == 0)
    {
        float *L = (float *)malloc(n * n * sizeof(float));
        float *U = (float *)malloc(n * n * sizeof(float));
        // Measures the total runtime of the benchmark
        clock_gettime(CLOCK_MONOTONIC, &start);
        for (int i = 0; i < repeats; i++)
        {
            ludecomp(n, A, L, U);
        }
        clock_gettime(CLOCK_MONOTONIC, &end);
        time_spent = (end.tv_sec - start.tv_sec) * BILLION +
                     (end.tv_nsec - start.tv_nsec);
    }
    else if (implementation == 1)
    {
        float *L = (float *)malloc(n * n * sizeof(float));
        float *U = (float *)malloc(n * n * sizeof(float));
        // Measures the total runtime of the benchmark
        clock_gettime(CLOCK_MONOTONIC, &start);
        for (int i = 0; i < repeats; i++)
        {
            ludecompV2(n, A, L, U);
        }
        clock_gettime(CLOCK_MONOTONIC, &end);
        time_spent = (end.tv_sec - start.tv_sec) * BILLION +
                     (end.tv_nsec - start.tv_nsec);
    }
    printf("Gesamtlaufzeit: %lf Nanosekunden\n", time_spent);
    // returns the average runtime
    return time_spent / repeats;
}

size_t getSizeMatrix(char *filename)
{
    // open file
    FILE *file = fopen(filename, "r");
    // check for invalid file

    if (file == NULL)
    {
        printf("getSizeMatrix_error opening file: \"%s\"!\n", filename);
        exit(EXIT_FAILURE);
    }

    // get size of matrix
    size_t n = 0;  // [
    size_t n1 = 0; // ]

    size_t n2 = 0; // ,

    char c;

    while ((c = fgetc(file)) != EOF)
    {
        if (c == '[')
        {
            n++;
        }
        else if (c == ']')
        {
            n1++;
        }
        else if (c == ',')
        {
            n2++;
        }
    }
    // checks if the input matrix is square
    if (n != n1)
    {
        printf("Wrong matrix input\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }
    if (n2 != n * (n - 1))
    {
        printf("Wrong matrix input\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    fclose(file);
    return n;
}

int main(int argc, char *argv[])
{
    // check for helper commands
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0)
        {
            usage();
            exit(EXIT_SUCCESS);
        }
    }
    if (argc <= 1)
    {
        usage();
        exit(EXIT_FAILURE);
    }

    char *filename = argv[1];

    int implementation = 0;
    int tests = 0;
    bool benchmark = false;
    int benchmark_repeats = 1;
    char *output_filename = NULL;
    float *A = load_matrix(filename);
    size_t size = getSizeMatrix(filename);

    unsigned long long int temp_n = size;
    // checks for size overflow
    if (__builtin_umulll_overflow(temp_n, temp_n, &temp_n) || temp_n <= 0)
    {
        printf("size overflow/underflow of matrix\n");
        exit(EXIT_FAILURE);
    }

    float L[size * size];
    float U[size * size];
    int opt;
    while ((opt = getopt(argc, argv, "V:B:r:o:t:h")) != -1)
    {
        switch (opt)
        {
        case 'V':
            implementation = atoi(optarg);
            // 0 = Basic implementation
            // 1 = Optimized implementation
            if (implementation < 0 || implementation > 1)
            {
                fprintf(stderr, "Unknown implementation: %d\n", implementation);
                usage();
                exit(EXIT_FAILURE);
            }
            break;

        case 'B':
            benchmark = true;
            // Number of repetitions of the benchmark
            benchmark_repeats = atoi(optarg);
            if (benchmark_repeats <= 0)
            {
                fprintf(stderr, "Invalid benchmark repeats: %d\n", benchmark_repeats);
                usage();
                exit(EXIT_FAILURE);
            }
            break;
        case 'r':
            // Size n of matrix
            size = atoi(optarg);
            if (size <= 0)
            {
                fprintf(stderr, "Invalid size: %lu\n", size);
                usage();
                exit(EXIT_FAILURE);
            }
            // Generation of matrix in generate_random_matrix
            generate_random_matrix(size);
            exit(EXIT_SUCCESS);
        case 'o':
            output_filename = optarg;
            break;
        case 'h':
            usage();
            exit(EXIT_SUCCESS);
        case 't':
            // The chosen test set
            tests = atoi(optarg);
            // executing chosen test set
            if (tests == 0)
            {
                allTestCases();
            }
            else if (tests == 1)
            {
                testCasesSmall();
            }
            else if (tests == 2)
            {
                testCasesLarge();
            }
            else if (tests == 3)
            {
                testCasesEdge();
            }

            else if (tests < 0 || tests > 3)
            {
                fprintf(stderr, "Unknown testset: %d\n", tests);
                usage();
                test_usage();
                exit(EXIT_FAILURE);
            }
            break;
        default:
            fprintf(stderr, "Unknown option: %c\n", optopt);
            usage();
            exit(EXIT_FAILURE);
        }
    }
    if (implementation == 0)
    {
        ludecomp(size, A, L, U);
        if (output_filename != NULL)
        {
            save_output_matrix(output_filename, L, U, size);
        }
    }
    else if (implementation == 1)
    {
        ludecompV2(size, A, L, U);
        if (output_filename != NULL)
        {
            save_output_matrix(output_filename, L, U, size);
        }
    }
    if (benchmark == true)
    {
        double timeSpent = benchmarkEXE(benchmark_repeats, A, size, implementation);
        printf("Durchschnittliche Laufzeit: %lf Nanosekunden\n", timeSpent);
    }

    return EXIT_SUCCESS;
}
