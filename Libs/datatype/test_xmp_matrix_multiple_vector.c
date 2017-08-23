#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <xmp.h>

int main(void){
double m[6][6] = {{1, 0, 2.7, 0, 0, 0}, {2, 0, 1, 0, -2.5, 0}, {9, 0, 0, -3, 0, 0}, {0, 0, 0, 10.8, 0, -1.11}, {0, -4.8, 0, 0, -3.33, 0}, {0, -2.1, 0, 0, 0, 0}};
double a = 1, b = 2, c = -1, d = -2, e = 1, f = 1;
/**
	matrix mat;
	matrix_ELL matell;
	matrix_init(&mat, 1, 1);
	for(int i=0; i<6; i++){
		stock_mvector_in_matrix(&mat, (void **)&m[i], i, 6);
	}
	//matrix_show(&mat);
	matrix_convert_matrix_ell(&mat, &matell);
	matrix_ell_show(&matell);
**/
	vector v, newV;
	vector_init(&v, 6);
	vector_add(&v, &a);
	vector_add(&v, &b);
	vector_add(&v, &c);
	vector_add(&v, &d);
	vector_add(&v, &e);
	vector_add(&v, &f);
	vector_show(&v);

	//matrix_ell_multiple_vector(&matell, &v, &newV);
	//vector_show(&newV);
}