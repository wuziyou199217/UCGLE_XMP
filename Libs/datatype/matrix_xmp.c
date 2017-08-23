#include <stdio.h>
#include <stdlib.h>
#include <xmp.h>
#include "matrix_xmp.h"

int matrix_total_ligne(matrix * mat, int ligne){
	return mat->total[ligne];
}

int matrix_get_ligne(matrix * mat){
	return mat->ligne;
}

int matrix_get_colone(matrix * mat){
	return mat->colone;
}

int * matrix_total(matrix * mat){
	return mat->total;
}

void *** matrix_items(matrix * mat){
	return mat->items;
}

static void matrix_init_total(matrix * mat, int start, int end){
	for(int i=start; i<end; i++){
		mat->total[i] = 0;
	}
}

void matrix_complete_ligne(matrix * mat){
	double a = 0;
	for(int i=0; i<mat->ligne; i++){
		if(matrix_total_ligne(mat, i) < mat->colone){
			//printf("number: %d, col_sum: %d\n", matrix_total(mat, i), mat->colone);
			for(int j=matrix_total_ligne(mat, i); j<mat->colone; j++){
				matrix_add_duplicate(mat, i, &a);
			}
		}
	}
}

void matrix_init(matrix * mat, int ligne, int colone){
	mat->ligne = ligne;
	mat->colone = colone;
	//printf("ligne: %d, colone: %d\n", mat->ligne, mat->colone);
	mat->total = xmp_malloc(sizeof(int), ligne);
	matrix_init_total(mat, 0, ligne);
	mat->items = xmp_malloc(sizeof(void *), ligne);
	for(int i=0; i<ligne; i++){
		mat->items[i] = xmp_malloc(sizeof(void *), colone);
	}
}

void matrix_add(matrix * mat, int ligne, void * item){
	if(mat->ligne == ligne){
		printf("Matrix: Out of dimension of ligne\n");
		return;
	}
	if(mat->total[ligne] == mat->colone){
		printf("Matrix: Out of dimension of colone\n");
		return;
	}
	mat->items[ligne][mat->total[ligne]++] = item;
	//printf("the new value position is (%d, %d), the ligne is %d\n", ligne + 1, mat->total[ligne], mat->ligne);
}

void matrix_add_duplicate(matrix * mat, int ligne, void * item){
	void * item_dup = xmp_malloc(xmp_desc_of(item_dup), 1);
	if(mat->ligne == ligne){
		printf("Matrix: Out of dimension of ligne\n");
		return;
	}
	if(mat->total[ligne] == mat->colone){
		printf("Matrix: Out of dimension of colone\n");
		return;
	}
	*(double *)item_dup = *(double *)item;
	mat->items[ligne][mat->total[ligne]++] = item_dup;
}

void matrix_copy(matrix * mat1, matrix * mat2){
	matrix_init(mat2, mat1->ligne, mat1->colone);
	for(int i=0; i<mat1->ligne; i++){
		for(int j=0; j<mat1->colone; j++){
			matrix_add(mat2, i, matrix_get(mat1, i, j));
		}
	}
}

void matrix_duplicate(matrix * mat1, matrix * mat2){
	matrix_init(mat2, mat1->ligne, mat1->colone);
	for(int i=0; i<mat1->ligne; i++){
		for(int j=0; j<mat1->colone; j++){
			matrix_add_duplicate(mat2, i, matrix_get(mat1, i, j));
		}
	}
}

void matrix_set(matrix * mat, int ligne, int colone, void * item){
	if(colone >= 0 && colone < mat->total[ligne]){
		*(double *)mat->items[ligne][colone] = *(double *)item;
	}
}

void matrix_transpose(matrix * mat1, matrix * mat2){
	matrix_init(mat2, matrix_get_colone(mat1), matrix_get_ligne(mat1));
	for(int i=0; i<matrix_get_colone(mat1); i++){
		for(int j=0; j<matrix_get_ligne(mat1); j++){
			matrix_add_duplicate(mat2, i, matrix_get(mat1, j, i));
		}
	}
}

void * matrix_get(matrix * mat, int ligne, int colone){
	if(colone >= 0 && colone < mat->total[ligne]){
		return mat->items[ligne][colone];
	}else{
		return NULL;
	}
}

void matrix_get_vector(matrix * mat, vector * v, int ligne){
	vector_init(v, matrix_total_ligne(mat, ligne));
	for(int i=0; i<matrix_total_ligne(mat, ligne); i++){
		vector_add_duplicate(v, matrix_get(mat, ligne, i));
	}
}

void matrix_delete(matrix * mat, int ligne, int colone){
	if(colone >= 0 && colone < matrix_total_ligne(mat, ligne)){
		for(int i=colone; i<matrix_total_ligne(mat, ligne)-1; i++){
			mat->items[ligne][i] = mat->items[ligne][i + 1];
		}
		mat->total[ligne]--;
	}else{
		return;
	}
}

void matrix_delete_ligne(matrix * mat, matrix * newm, int ligne){
	if(ligne >=0 && ligne < mat->ligne){
		matrix_init(newm, mat->ligne - 1, mat->colone);
		for(int i=0; i<mat->ligne; i++){
			if(i != ligne){
				for(int j=0; j<mat->colone; j++){
					if(i < ligne){
						matrix_add_duplicate(newm, i, matrix_get(mat, i, j));
					}else if(i > ligne){
						matrix_add_duplicate(newm, i - 1, matrix_get(mat, i, j));
					}
				}
			}
		}
	}
}

void matrix_delete_colone(matrix * mat, matrix * newm, int colone){
	matrix_init(newm, mat->ligne, mat->colone - 1);
	for(int i=0; i<mat->ligne; i++){
		for(int j=0; j<mat->colone; j++){
			if(j != colone){
				matrix_add_duplicate(newm, i, matrix_get(mat, i, j));
			}
		}
	}
}

void matrix_free(matrix * mat){
	mat->ligne = 0;
	mat->colone = 0;
	free(mat->items);
	free(mat->total);
	mat->items = NULL;
	mat->total = NULL;

}

void matrix_show(matrix * mat){
	for(int i=0; i<mat->ligne; i++){
		for(int j=0; j<mat->colone; j++){
			printf("%f ", *(double *)matrix_get(mat, i, j));
		}
		printf("\n");
	}
	printf("\n\n");
}

/**********************************
Matrix Ellpack
***********************************/
int matrix_ell_total_ligne(matrix_ELL * mat, int ligne){
	return mat->total[ligne];
}

int matrix_ell_get_ligne(matrix_ELL * mat){
	return mat->ligne;
}

int matrix_ell_get_colone(matrix_ELL * mat){
	return mat->colone;
}

int matrix_ell_n_colone(matrix_ELL * mat){
	return mat->n_colone;
}

int * matrix_ell_total(matrix_ELL * mat){
	return mat->total;
}

void *** matrix_ell_items(matrix_ELL * mat){
	return mat->items;
}

void matrix_ell_init(matrix_ELL * mat, int ligne, int colone, int n_colone){
	mat->n_colone = n_colone;
	mat->ligne = ligne;
	mat->colone = colone;
	//printf("ligne: %d, colone: %d\n", mat->ligne, mat->colone);
	mat->total = xmp_malloc(sizeof(int), ligne);
	matrix_ell_init_total(mat, 0, ligne);
	mat->items = xmp_malloc(sizeof(void *), ligne);
	for(int i=0; i<ligne; i++){
		mat->items[i] = xmp_malloc(sizeof(void *), colone);
	}
}

static void matrix_ell_init_total(matrix_ELL * mat, int start, int end){
	for(int i=start; i<end; i++){
		mat->total[i] = 0;
	}
}

void matrix_ell_complete_ligne(matrix_ELL * mat){
	double a = -1;
	for(int i=0; i<mat->ligne; i++){
		if(matrix_ell_total_ligne(mat, i) < mat->colone){
			//printf("number: %d, col_sum: %d\n", matrix_total(mat, i), mat->colone);
			for(int j=0; j<mat->colone; j++){
				if(!matrix_ell_get(mat, i, j)){
					matrix_ell_add_duplicate(mat, i, j, &a);
				}			
			}
		}
	}
}

void matrix_ell_add(matrix_ELL * mat, int ligne, int colone, void * item){
	if(mat->ligne == ligne){
		printf("Matrix: Out of dimension of ligne\n");
		return;
	}
	if(colone == mat->colone){
		printf("Matrix: Out of dimension of colone\n");
		return;
	}
	mat->total[ligne]++;
	mat->items[ligne][colone] = item;
	//printf("the new value position is (%d, %d), the ligne is %d\n", ligne + 1, mat->total[ligne], mat->ligne);
}

void matrix_ell_add_duplicate(matrix_ELL * mat, int ligne, int colone, void * item){
	void * item_dup = xmp_malloc(xmp_desc_of(item_dup), 1);
	if(mat->ligne == ligne){
		printf("Matrix: Out of dimension of ligne\n");
		return;
	}
	if(colone == mat->colone){
		printf("Matrix: Out of dimension of colone\n");
		return;
	}
	*(double *)item_dup = *(double *)item;
	mat->total[ligne]++;
	mat->items[ligne][colone] = item_dup;
}

void matrix_ell_copy(matrix_ELL * mat1, matrix_ELL * mat2){
	matrix_ell_init(mat2, mat1->ligne, mat1->colone, mat1->n_colone);
	for(int i=0; i<mat1->ligne; i++){
		for(int j=0; j<mat1->colone; j++){
			matrix_ell_add(mat2, i, j, matrix_ell_get(mat1, i, j));
		}
	}
}

void matrix_ell_duplicate(matrix_ELL * mat1, matrix_ELL * mat2){
	matrix_ell_init(mat2, mat1->ligne, mat1->colone, mat1->n_colone);
	for(int i=0; i<mat1->ligne; i++){
		for(int j=0; j<mat1->colone; j++){
			matrix_ell_add_duplicate(mat2, i, j, matrix_ell_get(mat1, i, j));
		}
	}
}

void matrix_ell_set(matrix_ELL * mat, int ligne, int colone, void * item){
	if(colone >= 0 && colone < mat->total[ligne]){
		*(double *)mat->items[ligne][colone] = *(double *)item;
	}
}



void * matrix_ell_get(matrix_ELL * mat, int ligne, int colone){
	return mat->items[ligne][colone];
}



void matrix_ell_free(matrix_ELL * mat){
	mat->n_colone = 0;
	mat->ligne = 0;
	mat->colone = 0;
	free(mat->items);
	free(mat->total);
	mat->items = NULL;
	mat->total = NULL;
}

void matrix_ell_show(matrix_ELL * mat){
	int flag = 0;
	for(int i=0; i<mat->ligne; i++){
		for(int j=0; j<mat->n_colone; j++){
			for(int k=0; k<mat->colone/2; k++){
				if(*(double *)matrix_ell_get(mat, i, k) == (double)j){
					printf("%f ", *(double *)matrix_ell_get(mat, i, mat->colone/2 + k));
					flag = 1;
				}
			}
			if(flag == 0){
				printf("%f ", (double)0);
			}else if(flag == 1){
				flag = 0;
			}
		}
		printf("\n");
	}
	printf("\n\n");
}