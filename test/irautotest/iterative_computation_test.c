// 迭代计算性能测试用例
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define ITERATIONS 10000000

float compute_pi() {
    float x, y, pi;
    int count = 0;
    
    srand(time(NULL));
    
    for (int i = 0; i < ITERATIONS; i++) {
        x = (float)rand() / RAND_MAX;
        y = (float)rand() / RAND_MAX;
        
        if (x*x + y*y <= 1.0) {
            count++;
        }
    }
    
    pi = 4.0 * count / ITERATIONS;
    return pi;
}

float newton_sqrt(float x, int iterations) {
    float result = 1.0;
    
    for (int i = 0; i < iterations; i++) {
        result = 0.5 * (result + x / result);
    }
    
    return result;
}

int main() {
    clock_t start, end;
    double cpu_time_used;
    
    printf("Starting computation...\n");
    
    start = clock();
    float pi_approx = compute_pi();
    end = clock();
    
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Monte Carlo Pi approximation: %f (computed in %f seconds)\n", pi_approx, cpu_time_used);
    
    start = clock();
    float sqrt_result = 0.0;
    for (int i = 1; i <= 1000; i++) {
        sqrt_result += newton_sqrt((float)i, 1000);
    }
    end = clock();
    
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Newton square root sum: %f (computed in %f seconds)\n", sqrt_result, cpu_time_used);
    
    return 0;
}
