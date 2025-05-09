// 矩阵乘法性能测试用例
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define N 50

float A[N][N];
float B[N][N];
float C[N][N];

void init_matrices() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = (float)rand() / RAND_MAX * 10.0;
            B[i][j] = (float)rand() / RAND_MAX * 10.0;
            C[i][j] = 0.0;
        }
    }
}

void matrix_multiply() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

float compute_checksum() {
    float sum = 0.0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            sum += C[i][j];
        }
    }
    return sum;
}

int main() {
    clock_t start, end;
    double cpu_time_used;
    
    srand(time(NULL));
    init_matrices();
    
    start = clock();
    matrix_multiply();
    end = clock();
    
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    float checksum = compute_checksum();
    
    printf("Matrix multiplication 50x50 completed in %f seconds\n", cpu_time_used);
    printf("Checksum: %f\n", checksum);
    
    return 0;
}
