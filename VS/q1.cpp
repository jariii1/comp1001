/*
------------------DR VASILIOS KELEFOURAS-----------------------------------------------------
------------------COMP1001 ------------------------------------------------------------------
------------------COMPUTER SYSTEMS MODULE-------------------------------------------------
------------------UNIVERSITY OF PLYMOUTH, SCHOOL OF ENGINEERING, COMPUTING AND MATHEMATICS---
*/


#include <stdio.h> //this library is needed for printf function
#include <stdlib.h> //this library is needed for rand() function
#include <windows.h> //this library is needed for pause() function on Windows OS
#include <time.h> //this library is needed for clock() function
#include <math.h> //this library is needed for abs()
#include <omp.h> //this library is needed for the timer
#include <immintrin.h> //this library is needed for SIMD intrinsics

unsigned short int equal(float a, float b); //in C, functions must be declared before main()
void init();
void q1_vec();
void q2_vec();
void q3_vec();


#define N 256 //input size
#define EPSILON 1e-6 //relative error margin

float A[N][N], u1[N], u2[N], v1[N], v2[N], x[N], y[N], w[N], z[N] ;
float alpha=0.23, beta=0.45;	


int main() {

	double start_1, end_1; //define the timers measuring execution time

	init();//initialize the arrays

	start_1 = omp_get_wtime(); //start the timer 
	 
	q1_vec(); 
	q2_vec();
	q3_vec();
		
	end_1 = omp_get_wtime(); //end the timer 

	printf(" Time in seconds is %f\n", end_1 - start_1 );//print the ex.time
	
	system("pause"); //this command does not let the output window to close
	
	return 0; //normally, by returning zero, we mean that the program ended successfully. 
}


void init() {

int i,j;

        for (i=0;i<N;i++)
        for (j=0;j<N;j++){
            A[i][j]= 0.0f;

        }

        for (i=0;i<N;i++){
            u1[i]=(i%9)*0.22f;
            u2[i]=(i%9)*0.33f;
            v1[i]=(i%9)*0.44f;
            v2[i]=(i%9)*0.55f;
            w[i]=0.0f;
        }
        
}


void q1_vec() {
    __m128 a = _mm_set1_ps(alpha);   // [alpha alpha alpha alpha]
    __m128 b = _mm_set1_ps(beta);    // [beta  beta  beta  beta ]

    for (int i = 0; i < N; i++) {
        w[i] = alpha * u1[i] + beta; //scalar version for verification

        __m128 u = _mm_loadu_ps(&u1[i]);      // load 4 floats
        __m128 mul = _mm_mul_ps(a, u);        // alpha * u
        __m128 res = _mm_add_ps(mul, b);      // + beta
        _mm_storeu_ps(&w[i], res);            // store result
    }
}


void q2_vec() {
    for (int i = 0; i < N; i++) {

        __m128 u1_vec = _mm_set1_ps(u1[i]);   // [u1[i] u1[i] u1[i] u1[i]]
        __m128 u2_vec = _mm_set1_ps(u2[i]);   // [u2[i] u2[i] u2[i] u2[i]]

        for (int j = 0; j < N; j += 4) {

            __m128 v1_vec = _mm_loadu_ps(&v1[j]);     // 4 v1’s
            __m128 v2_vec = _mm_loadu_ps(&v2[j]);     // 4 v2’s
            __m128 a_vec  = _mm_loadu_ps(&A[i][j]);   // 4 A’s

            __m128 mul1 = _mm_mul_ps(u1_vec, v1_vec); //4 multiplications
            __m128 mul2 = _mm_mul_ps(u2_vec, v2_vec); //4 multiplications
            __m128 sum  = _mm_add_ps(mul1, mul2); //4 additions

            __m128 res = _mm_add_ps(a_vec, sum); //4 additions

            _mm_storeu_ps(&A[i][j], res); //store results
        }
    }
}


void q3_vec() {
    for (int i = 0; i < N; i++) {

        __m128 num3 = _mm_setzero_ps();       // vector accumulator

        for (int j = 0; j < N; j += 4) {

            __m128 a = _mm_loadu_ps(&A[i][j]);   // A[i][j..j+3]
            __m128 u = _mm_loadu_ps(&u1[j]);     // u1[j..j+3]

            __m128 prod = _mm_mul_ps(a, u);     // 4 products
            num3 = _mm_add_ps(num3, prod);        // accumulate
        }

        // horizontal sum of num3’s 4 lanes
        float tmp[4];
        _mm_storeu_ps(tmp, num3);
        float sum = tmp[0] + tmp[1] + tmp[2] + tmp[3];

        w[i] += alpha * sum;
    }
}



//this function becomes problematic when b is zero or when both a and b are zero
unsigned short int equal(float a, float b) {
	float temp = a - b;

	if (fabs(temp/b) < EPSILON)
		return 0; //success
	else
		return 1; //wrong result
}



