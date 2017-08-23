#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "arnoldi_gmres.h"

int main(void){
	srand(time(NULL));
	double m[ROWS_NUM][COLS_NUM] = {{0}};
	for(int i=0; i<ROWS_NUM; i++){
		for(int j=0; j<COLS_NUM; j++){
			if(j == i + 1 || j == i || j == i - 1){
				m[i][j] = random_get(-10, 10);
			}
		}
	}
/**
	matrix mat;
	//matrix_ELL matell;
	matrix_init(&mat, matrix_size, matrix_size);
	for(int i=0; i<matrix_size; i++){
		stock_mvector_in_matrix(&mat, (void **)&m[i], i, matrix_size);
	}
	//matrix_show(&mat);
	//matrix_convert_matrix_ell(&mat, &matell);
	//matrix_ell_show(&matell);
**/
	double a = 1;
	vector v;
	vector_init(&v, ROWS_NUM);
	for(int i=0; i<ROWS_NUM; i++){
		vector_add_duplicate(&v, (void *)&a);
	}
	//vector_show(&v);

	matrix matQ, matH, matT;
	int restart_max = 100;
	matrix_init(&matQ, restart_max, COLS_NUM);
	matrix_init(&matH, restart_max, restart_max);
	//printf("matQ: %p, matH: %p, matT: %p, mat: %p, matell: %p\n", &matQ, &matH, &matT, &mat, &matell);

	

	arnoldi_xmp(m, &v, &matQ, &matH, restart_max);
	hessenberg_qr(&matH, &matT, 100);
	
	//matrix_show(&mat);
	matrix_show(&matQ);
	matrix_show(&matH);
	matrix_show(&matT);

	vector_free(&v);
	//matrix_free(&mat);
	matrix_free(&matQ);
	matrix_free(&matH);
	matrix_free(&matT);
	//matrix_ell_free(&matell);
}