/*
 * Tema 2 ASC
 * 2022 Spring
 */
#include "utils.h"
#include "cblas.h"
/*
 * Add your BLAS implementation here
 */

double *my_solver(int N, double *A, double *B) {
        cblas_dtrmm(CblasRowMajor,
		   CblasRight,
		   CblasUpper,
		   CblasTrans,
		   CblasNonUnit,
		    N, N, 1, A, N, A, N);
	
	double *C = malloc(N * N * sizeof(double));
	cblas_dgemm(CblasRowMajor,
		    CblasTrans,
		    CblasNoTrans,
		    N, N, N, 1, B, N, B, N, 0, C, N); 

	cblas_dsymm(CblasRowMajor,
		    CblasRight,
		    CblasUpper,
		    N, N, 1, A, N, B, N, 1, C, N);
	       
	return C;
}
