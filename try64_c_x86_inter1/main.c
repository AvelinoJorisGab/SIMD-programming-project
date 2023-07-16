#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double computeDotProductC(int n, double* A, double* B);
double generateRandomValue();

double computeDotProductC(int n, double* A, double* B) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += (double)A[i] * (double)B[i];
    }
    return sum;
}

extern double computeDotProductASM(int n, double* A, double* B);

double generateRandomValue() {
    return (double)(rand() % 100) + 1;
}

int main() {
    int n = 1 << 20;  // Vector size n = 2^20
    double* A = (double*)malloc(sizeof(double) * n);
    double* B = (double*)malloc(sizeof(double) * n);

    if (A == NULL || B == NULL) {
        printf("Memory allocation failed. Exiting...\n");
        return 1;
    }

    // Initialize vectors A and B with random values
    srand((unsigned int)time(NULL));
    for (int i = 0; i < n; i++) {
        A[i] = generateRandomValue();
        B[i] = generateRandomValue();
    }

    // Compute dot product using C version
    clock_t start = clock();
    double dotProductC = computeDotProductC(n, A, B);
    clock_t end = clock();
    double cpu_time_used_c = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Compute dot product using ASM version
    //start = clock();
    double dotProductASM = computeDotProductASM(n, A, B);
    //end = clock();
    //double cpu_time_used_asm = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Dot Product (C): %lf\n", dotProductC);
    printf("Time taken (C): %lf seconds\n", cpu_time_used_c);

    printf("Dot Product (ASM): %lf\n", dotProductASM);
    //printf("Time taken (ASM): %lf seconds\n", cpu_time_used_asm);

    //Print the random values used
    //printf("Random values:\n");
    //for (int i = 0; i < n; i++) {
    //    printf("A[%d] = %lf, B[%d] = %lf\n", i, A[i], i, B[i]);
    //}

    // Clean up
    free(A);
    free(B);

    return 0;
}