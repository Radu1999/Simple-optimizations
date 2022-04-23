/*
 * Tema 2 ASC
 * 2022 Spring
 */
#include "utils.h"

/*
 * Add your unoptimized implementation here
 */

#define max(a, b)                                                              \
	({                                                                     \
		__typeof__(a) _a = (a);                                        \
		__typeof__(b) _b = (b);                                        \
		_a > _b ? _a : _b;                                             \
	})

double *multiply_with_transpose(int N, double *A, int triangularA, int right)
{
	double *C = malloc(N * N * sizeof(double));
	for (int i = 0; i < N; i++) {
		for (int k = 0; k < N; k++) {
			double el = 0;
			for (int j = (triangularA ? max(i, k) : 0); j < N;
			     j++) {
				if (right) {
					el += A[i * N + j] * A[k * N + j];
				} else {
					el += A[j * N + i] * A[j * N + k];
				}
			}
			C[i * N + k] = el;
		}
	}
	return C;
}

double *multiply(int N, double *A, int triangularA, double *B)
{
	double *C = malloc(N * N * sizeof(double));
	for (int i = 0; i < N; i++) {
		for (int k = 0; k < N; k++) {
			double el = 0;
			for (int j = (triangularA ? i : 0); j < N; j++) {
				el += A[i * N + j] * B[j * N + k];
			}
			C[i * N + k] = el;
		}
	}
	return C;
}

double *add(int N, double *A, double *B)
{
	double *C = malloc(N * N * sizeof(double));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			C[i * N + j] = A[i * N + j] + B[i * N + j];
		}
	}
	return C;
}
double *my_solver(int N, double *A, double *B)
{
	double *AAT = multiply_with_transpose(N, A, 1, 1);
	double *BAAT = multiply(N, B, 0, AAT);
	double *BTB = multiply_with_transpose(N, B, 0, 0);

	double *C = add(N, BAAT, BTB);
	free(AAT);
	free(BAAT);
	free(BTB);

	return C;
}
