#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "arnoldi_gmres.h"

int main(void){
	double m[6][6] = {{1, 0, 2.7, 0, 0, 0}, {2, 0, 1, 0, -2.5, 0}, {9, 0, 0, -3, 0, 0}, {0, 0, 0, 10.8, 0, -1.11}, {0, -4.8, 0, 0, -3.33, 0}, {0, -2.1, 0, 0, 0, 0}};
	double a = 1, b = 2, c = -1, d = -2, e = 1, f = 1;
	double A = 1, B = 1, C = 1, D = 1, E = 1, F = 1;

	matrix mat;
	matrix_ELL matell;
	matrix_init(&mat, 1, 1);
	for(int i=0; i<6; i++){
		stock_mvector_in_matrix(&mat, (void **)&m[i], i, 6);
	}
	//matrix_show(&mat);

	matrix_convert_matrix_ell(&mat, &matell);
	matrix_ell_show(&matell);

	vector vb;
	vector_init(&vb);
	vector_add(&vb, &a);
	vector_add(&vb, &b);
	vector_add(&vb, &c);
	vector_add(&vb, &d);
	vector_add(&vb, &e);
	vector_add(&vb, &f);
	//vector_show(&vb);

	vector vx;
	vector_init(&vx);
	vector_add(&vx, &A);
	vector_add(&vx, &B);
	vector_add(&vx, &C);
	vector_add(&vx, &D);
	vector_add(&vx, &E);
	vector_add(&vx, &F);
	//vector_show(&vx);

	matrix matQ, matH, matR, omega;
	matrix_init(&matQ, 1, 1);
	matrix_init(&matH, 1, 1);
	matrix_init(&matR, 1, 1);
	matrix_init(&omega, 1, 1);
	matrix_add_duplicate(&omega, 0, (void *)&A);


	double * beta;
	beta = (double *)malloc(sizeof(double));

	gmres_ell(&matell, &vx, &vb, &matQ, &matH, &omega, &matR, 0, 5, beta);

	printf("matQ: %p, matH: %p, matR: %p, omega: %p, matell: %p\n", &matQ, &matH, &matR, &omega, &matell);

	vector v1, v2;
	matrix_ell_multiple_vector(&matell, &vx, &v1);
	vector_reduce_vector(&vb, &v1, &v2);

	matrix_show(&matQ);
	matrix_show(&matH);
	matrix_show(&omega);
	matrix_show(&matR);
	vector_show(&vx);
	vector_show(&v1);
	vector_show(&v2);

	matrix_free(&matQ);
	matrix_free(&matH);
	matrix_free(&omega);
	matrix_free(&matR);
	matrix_free(&mat);
	matrix_ell_free(&matell);
	vector_free(&vx);
	vector_free(&vb);
	vector_free(&v1);
	vector_free(&v2);
}