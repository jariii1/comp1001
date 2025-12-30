/*
------------------DR VASILIOS KELEFOURAS-----------------------------------------------------
------------------COMP1001 ------------------------------------------------------------------
------------------COMPUTER SYSTEMS MODULE-------------------------------------------------
------------------UNIVERSITY OF PLYMOUTH, SCHOOL OF ENGINEERING, COMPUTING AND MATHEMATICS---
*/

// compile with : gcc mmm.c -o p -O3 -fopenmp

#include <stdio.h>	/* for printf */
#include <stdint.h>	/* for uint64 definition */
#include <stdlib.h>	/* for exit() definition */
#include <time.h>	/* for clock_gettime */
#include <unistd.h> //for sleep
#include <pthread.h>//for cpu_set_t
#include <omp.h> //for openmp


int N, NUM_THREADS; //define matrix size and number of threads

//functions declaration
void MMM_init();
int MMM();

float *A, *B, *C; //define matrices as float pointers


int main(int argc, char *argv[]){

	if (argc != 3) {
		printf("Usage: %s <matrix_size> <num_threads>\n", argv[0]);
		return 1;
	}	

	N = atoi(argv[1]); //matrix size from command line
	NUM_THREADS = atoi(argv[2]); //number of threads from command line

	//allocate memory for matrices
	A = (float *)malloc(N * N * sizeof(float));
	B = (float *)malloc(N * N * sizeof(float));
	C = (float *)malloc(N * N * sizeof(float));

	if (A == NULL || B == NULL || C == NULL) {
		printf("Memory allocation failed\n");
		return 1;
	}

    MMM_init(); //initialize the arrays

    MMM(); //run the routine

	//free allocated memory
	free(A);
	free(B);
	free(C);

    return 0;

}



void MMM_init() {

	float e = 0.1234f, p = 0.7264f;

	//MMM
	for (unsigned int i = 0; i < N; i++) { 
		for (unsigned int j = 0; j < N; j++) {
			C[i][j] = 0.0f;
			A[i][j] = ( (j+i) % 99) + e; 
			B[i][j] = ( (j-i) % 99) - p; 
		}
	}
	   

}


void MMM(int N, int NUM_THREADS) {

    omp_set_num_threads(NUM_THREADS); //specify number of threads

    double start = omp_get_wtime(); //start time measurement

    #pragma omp parallel for private(j, k) //parallelize i loop
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            float sum = 0.0f; //local variable to hold the sum
            for (int k = 0; k < N; k++) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }

    double end = omp_get_wtime(); //end time measurement

    double execution_time = end - start; //calculate execution time

    double flops = (2.0 * N * N * N) / execution_time; //calculate FLOPs

    printf("Execution time: %f seconds\n", execution_time);
    printf("Performance:   %e FLOP/s\n", flops);
}






