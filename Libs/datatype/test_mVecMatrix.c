#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mVecMatrix.h"

int main(void){
	int i,j;
	double item = 5;
	double *inner_produit = malloc(sizeof(double));
	double *abs = malloc(sizeof(double));
	double a = 2.38, b = 7.65, c = 8.34, d = 105;
	double m[4][4] = {{1, 2, 2.7, 3.2}, {0, 1, -1, 2}, {0, 0, -3, 7}, {0, 0, 0, 3.5}};

	matrix mat, mati, matI;
	matrix_ELL matell;
	matrix_init(&mat, 4, 4);

	for(i=0; i<4; i++){
		stock_mvector_in_matrix(&mat, (void **)&m[i], i, 4);
	}

	upper_triangle_matrix_inverse(&mat, &mati);
	matrix_convert_matrix_ell(&mat, &matell);
	//matrix_ell_multiple_matrix(&matell, &mati, &matI);
	matrix_multiple_matrix(&mat, &mati, &matI);
	//matrix_show(&mat);

	vector v, w, vw, v_1, newV;
	vector_init(&v, 4);
	vector_init(&w, 4);

	vector_add_duplicate(&v, &a);
	vector_add_duplicate(&v, &b);
	vector_add_duplicate(&v, &c);
	vector_add_duplicate(&v, &d);
	vector_show(&v);

	//vector_divid(&v, item);
	//vector_show(&v);

	//vector_multiple(&v, item);
	//vector_show(&v);

	vector_add_duplicate(&w, &b);
	vector_add_duplicate(&w, &d);
	vector_add_duplicate(&w, &a);
	vector_add_duplicate(&w, &c);
	vector_show(&w);

	vector_inner_produit(&v, &w, inner_produit);
	vector_abs(&v, abs);
	printf("%f %f\n\n", *inner_produit, *abs);

	vector_add_vector(&v, &w, &vw);
	vector_reduce_vector(&vw, &w, &v_1);
	matrix_multiple_vector(&mat, &v, &newV);

	vector_show(&vw);
	vector_show(&v_1);
    vector_show(&newV);
  
    matrix_show(&mat);
    matrix_show(&mati);
    matrix_show(&matI);
    matrix_ell_show(&matell);


    vector q;
    matrix_get_vector(&mat, &q, 2);
    vector_show(&q);

    vector_free(&v);
    vector_free(&q);
    vector_free(&w);
	vector_free(&vw);
	vector_free(&newV);
	matrix_free(&mat);
	matrix_free(&mati);
	free(inner_produit);
	free(abs);
	inner_produit = NULL;
	abs = NULL;
}