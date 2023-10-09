#include <time.h>
#include <stdlib.h>
#include <stdio.h>

float dp(long N, float *pA, float *pB) {
    float R = 0.0;
    int j;
    for (j = 0; j < N; j++) {
        R += pA[j] * pB[j];
    }   
    return R;
}

int main(int argc, char *argv[]) {
    long vectorSize = atol(argv[1]);
    int numReps = atoi(argv[2]);
    int verbose = 0;
    if (argc > 3) {
        verbose = atoi(argv[3]);
    } 

    float *arr1 = (float*) malloc(vectorSize * sizeof(float));
    float *arr2 = (float*) malloc(vectorSize * sizeof(float));

    double totalTime = 0.0;
    float dotProdResult;

    for (int i = 0; i < vectorSize; i++) {
        arr1[i] = 1.0;
        arr2[i] = 1.0;
    }

    for (int i = 0; i < numReps; i++) {
        struct timespec start, stop;
        clock_gettime(CLOCK_MONOTONIC, &start);
        dotProdResult = dp(vectorSize, arr1, arr2);
        
        clock_gettime(CLOCK_MONOTONIC, &stop);

        double timeSec = (((double)stop.tv_sec + (double)stop.tv_nsec / 1000000000) - ((double)start.tv_sec + (double)start.tv_nsec / 1000000000));
        
        if (i >= numReps / 2) {
            totalTime += timeSec;
        }
    }

    if (verbose == 1) {
        printf("Dot Product Result: %f\n", dotProdResult);
        printf("\n");
    }


    double avgTime = totalTime / (numReps / 2);
    double bw = 2 * vectorSize * (sizeof(float) / 1E9) / avgTime;
    double flops = (2 * vectorSize) / avgTime;

    printf("N: %ld   <T>: %lf sec   B: %f GB/sec   F: %f FLOP/sec\n", vectorSize, avgTime, bw, flops);
    return 0;
}