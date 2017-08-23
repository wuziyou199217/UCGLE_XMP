#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

int main(void){
	int i,j;
	double a[10][4] = {{1, 2, 2.7, 3.2}, {2, 0, 1, 0}, {9, 10, -3, 7}, {5, 0, 4.7, 0}, {3, 6, 2.2, 6.8}, {2, 9, 1.1, 3.2}, {8, 0, 1.2, 0}, {4, 9, -7.8, 2.6}, {6, 10, 6, 4}, {1, 10, 8.4, 1}};

	//test for initialization of an array
	matrix mat, mat1, mat2, mat3;
	vector v;
	matrix_init(&mat, 10, 4);

	for(i=0; i<10; i++){
		for(j=0; j<4; j++){
			matrix_add(&mat, i, (void *)&a[i][j]);
		}
	}

	
	//matrix_duplicate(&mat, &mat1);
	matrix_transpose(&mat, &mat1);

	matrix_copy(&mat, &mat2);
	matrix_duplicate(&mat, &mat3);

	//matrix_show(&mat1);
	//matrix_show(&mat2);
	//matrix_show(&mat3);
	

	matrix_set(&mat, 4, 0, &a[5][1]);

	a[5][1] = 9.99;

	matrix_show(&mat);
	//matrix_show(&mat1);
	//matrix_show(&mat2);
	//matrix_show(&mat3);

	matrix_delete(&mat, 1, 0);

	matrix_get_vector(&mat, &v, 1);

	matrix_add(&mat, 1, &a[4][2]);

	//printf("%d\n", matrix_total(&mat, 4));

	matrix_show(&mat);

	vector_show(&v);

	//matrix_free(&mat);
	matrix_free(&mat1);
	matrix_free(&mat2);
	matrix_free(&mat3);
	vector_free(&v);
}