#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "arnoldi_gmres.h"

int main(void){
	double m[1000][1000] = {0};
	for(int i=0; i<1000; i++){
		for(int j=0; j<1000; j++){
			if(j == i + 1){
				m[i][j] = -1;
			}else if(j == i){
				m[i][j] = 2;
			}else if(j == i - 1){
				m[i][j] = -3;
			}
		}
	}

	matrix mat;
	matrix_ELL matell;
	matrix_init(&mat, 1000, 1000);
	for(int i=0; i<1000; i++){
		stock_mvector_in_matrix(&mat, (void **)&m[i], i, 1000);
	}
	//matrix_show(&mat);
	matrix_convert_matrix_ell(&mat, &matell);
	//matrix_ell_show(&matell);

	double a = 1;
	vector v;
	vector_init(&v, 1000);
	for(int i=0; i<1000; i++){
		vector_add_duplicate(&v, (void *)&a);
	}
	//vector_show(&v);

	matrix matQ, matH, matT;
	int restart_max = 1000;
	matrix_init(&matQ, restart_max, 1000);
	matrix_init(&matH, restart_max, restart_max);
	//printf("matQ: %p, matH: %p, matT: %p, mat: %p, matell: %p\n", &matQ, &matH, &matT, &mat, &matell);

	arnoldi(&mat, &v, &matQ, &matH, 0, restart_max);
	hessenberg_qr(&matH, &matT, 100);
	
	//matrix_show(&mat);
	matrix_show(&matQ);
	matrix_show(&matH);
	matrix_show(&matT);

	vector_free(&v);
	matrix_free(&mat);
	matrix_free(&matQ);
	matrix_free(&matH);
	matrix_free(&matT);
	matrix_ell_free(&matell);
}