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
	register int i_pos = 0;
	for (register int i = 0; i < N; ++i, i_pos += N) {
		register double *c = &C[i_pos];
		register int j_pos = 0;
		for (register int j = 0; j < N; ++j, j_pos += N) {
			register double *el = &B[j_pos + i];
			for (register int k = 0; k < N; k += 2) {
				asm("movlpd (%0), %%xmm0;"
				    "movhpd (%0), %%xmm0;"
				    "movapd (%1), %%xmm1;"
				    "mulpd %%xmm1, %%xmm0;"
				    "addpd (%2), %%xmm0;"
				    "movapd %%xmm0, (%2);"
				    :
				    : "a"(el), "b"(B + j_pos + k), "r"(c + k)
				    : "xmm0", "xmm1");
			}
		}
	}
	return C;
}

double *multiplyAAT(int N, double *A)
{
	double *C = calloc(N * N, sizeof(double));

	double rez[] = {0, 0};
	register int i_pos = 0;
	for (register int i = 0; i < N; ++i, i_pos += N) {
		register int j_pos = i_pos;
		for (register int j = i; j < N; ++j, j_pos += N) {
			register double el = 0;
			for (register int k = i % 2 == 0 ? i : i - 1; k < N;
			     k += 2) {
				asm("movapd (%0), %%xmm0;"
				    "movapd (%1), %%xmm1;"
				    "mulpd %%xmm1, %%xmm0;"
				    "movapd %%xmm0, (%2);"
				    :
				    : "a"(A + i_pos + k), "b"(A + j_pos + k),
				      "r"(rez)
				    : "xmm0", "xmm1");
				el += rez[0] + rez[1];
			}
			C[i_pos + j] = el;
		}
	}

	i_pos = N;
	for (register int i = 1; i < N; ++i, i_pos += N) {
		register int j_pos = 0;
		for (register int j = 0; j < i; ++j, j_pos += N) {
			C[i_pos + j] = C[j_pos + i];
		}
	}
	return C;
}

double *multiplyBAAT(int N, double *A, double *B)
{
	double *C = calloc(N * N, sizeof(double));
	double rez[] = {0, 0};
	register int i_pos = 0;
	for (register int i = 0; i < N; ++i, i_pos += N) {
		register int j_pos = 0;
		register double *a = &A[i_pos];
		for (register int j = 0; j < N; ++j, j_pos += N) {
			register double el = 0;
			register double *b = &B[j_pos];
			for (register int k = 0; k < N; k += 2) {
				asm("movapd (%0), %%xmm0;"
				    "movapd (%1), %%xmm1;"
				    "mulpd %%xmm1, %%xmm0;"
				    "movapd %%xmm0, (%2);"
				    :
				    : "a"(a + k), "b"(b + k), "r"(rez)
				    : "xmm0", "xmm1");

				el += rez[0] + rez[1];
			}
			C[i_pos + j] = el;
		}
	}
	return C;
}

void add(int N, double *A, double *B)
{
	register int i_pos = 0;
	for (register int i = 0; i < N; ++i, i_pos += N) {
		register double *a = &A[i_pos];
		register double *b = &B[i_pos];
		for (register int j = 0; j < N; ++j) {
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