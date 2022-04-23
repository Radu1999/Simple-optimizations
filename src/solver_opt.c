/*
 * Tema 2 ASC
 * 2022 Spring
 */
#include "utils.h"
/*
 * Add your optimized implementation here
 */

double *multiplyBTB(int N, double *B)
{
	double *C = calloc(N * N, sizeof(double));
	double rez[] = {0, 0};
	for (int i = 0; i < N; i++) {
		register double *c = &C[i * N];
		for (int j = 0; j < N; j++) {
			register double *el = &B[j * N + i];
			register double *b = &B[j * N];
			for (int k = 0; k < N; k += 2) {
				asm("movlpd (%0), %%xmm0;"
				    "movhpd (%0), %%xmm0;"
				    "movapd (%1), %%xmm1;"
				    "mulpd %%xmm1, %%xmm0;"
				    "movapd %%xmm0, (%2);"
				    :
				    : "a"(el), "b"(b + k), "r"(rez)
				    : "xmm0", "xmm1");

				*(c + k) += rez[0];
				*(c + k + 1) += rez[1];
			}
		}
	}
	return C;
}

double *multiplyAAT(int N, double *A)
{
	double *C = calloc(N * N, sizeof(double));

	double rez[] = {0, 0};
	for (int i = 0; i < N; i++) {
		for (int j = i; j < N; j++) {
			register double el = 0;
			register double *a1 = &A[i * N];
			register double *a2 = &A[j * N];
			for (int k = i % 2 == 0 ? i : i - 1; k < N; k += 2) {
				asm("movapd (%0), %%xmm0;"
				    "movapd (%1), %%xmm1;"
				    "mulpd %%xmm1, %%xmm0;"
				    "movapd %%xmm0, (%2);"
				    :
				    : "a"(a1 + k), "b"(a2 + k), "r"(rez)
				    : "xmm0", "xmm1");
				el += rez[0] + rez[1];
			}
			C[i * N + j] = el;
		}
	}

	for (int i = 1; i < N; i++) {
		register double *c = &C[i * N];
		register double *c2 = &C[i];
		register int pos = 0;
		for (int j = 0; j < i; j++) {
			*(c + j) = *(c2 + j * N);
			pos += N;
		}
	}
	return C;
}

double *multiplyBAAT(int N, double *A, double *B)
{
	double *C = calloc(N * N, sizeof(double));
	double rez[] = {0, 0};
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			register double el = 0;
			register double *a = &A[i * N];
			register double *b = &B[j * N];
			for (int k = 0; k < N; k += 2) {
				asm("movapd (%0), %%xmm0;"
				    "movapd (%1), %%xmm1;"
				    "mulpd %%xmm1, %%xmm0;"
				    "movapd %%xmm0, (%2);"
				    :
				    : "a"(a + k), "b"(b + k), "r"(rez)
				    : "xmm0", "xmm1");

				el += rez[0] + rez[1];
			}
			C[i * N + j] = el;
		}
	}
	return C;
}

void add(int N, double *A, double *B)
{
	for (int i = 0; i < N; i++) {
		register double *a = &A[i * N];
		register double *b = &B[i * N];
		for (int j = 0; j < N; j++) {
			*(a + j) += *(b + j);
		}
	}
}
double *my_solver(int N, double *A, double *B)
{
	double *AAT = multiplyAAT(N, A);
	double *BAAT = multiplyBAAT(N, B, AAT);
	double *BTB = multiplyBTB(N, B);

	add(N, BAAT, BTB);
	free(AAT);
	free(BTB);

	return BAAT;
}