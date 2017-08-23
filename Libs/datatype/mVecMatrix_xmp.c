#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mVecMatrix_xmp.h"
#include <xmp.h>

void vector_divid(vector * v, double x){
	int length = vector_total(v);
	double * items;
	items = xmp_malloc(xmp_desc_of(items), length);
	for(int i=0; i<length; i++){
		*(items + i) = (* vector_get(v, i))/x;
	}

	for(int i=0; i<length; i++){
		vector_set(v, i, (void *)(items + i));
	}
}

void vector_multiple(vector * v, double x){
	vector_divid(v, 1/x);
}

void vector_add_vector(vector * v1, vector * v2, vector * newV){
	if(vector_total(v1) != vector_total(v2)){
		printf("Not same dimension\n");
	}else{
		vector_init(newV, vector_total(v1));
		double * items = xmp_malloc(xmp_desc_of(items), vector_total(v1));
		for(int i=0; i<vector_total(v1); i++){
			*(items + i) = (* vector_get(v1, i)) + (* vector_get(v2, i));
			vector_add_duplicate(newV, items + i);
		}
	}
}

void vector_reduce_vector(vector * v1, vector * v2, vector * newV){
	vector_divid(v2, -1);
	vector_add_vector(v1, v2, newV);
	vector_divid(v2, -1);
}

void vector_inner_produit(vector * v1, vector * v2, double * h){
	* h = 0;
	if(vector_total(v1) != vector_total(v2)){
		printf("different dimention!\n");
	}else{
		int length = vector_total(v1);
		* h = 0;
		for(int i=0; i<length; i++){
			* h += (*(double *)vector_get(v1, i)) * (*(double *)vector_get(v2, i));
		}
	}
}

void vector_abs(vector * v, double * h){
	vector_inner_produit(v, v, h);
	* h = sqrt(* h);
}

void stock_vector_in_matrix(matrix * mat, vector * v, int ligne){
	if(matrix_get_colone(mat) > vector_total(v)){
		printf("Not matched!!!");
		return;
	}else{
		if(mat->ligne <= ligne){
			printf("Matrix: Out of dimension of ligne\n");
			return;
		}
		for(int i=0; i<vector_total(v); i++){
			if(i < matrix_total_ligne(mat, ligne)){
				matrix_set(mat, ligne, i, vector_get(v, i));
			}else{
				matrix_add_duplicate(mat, ligne, vector_get(v, i));
			}		
		}
	}
}

void stock_mvector_in_matrix(matrix * mat, void ** v, int ligne, int colone){
	if(matrix_get_colone(mat) > colone){
		printf("Not matched!!!");
		return;
	}else{
		if(mat->ligne <= ligne){
			if(mat->ligne == ligne){
				printf("Matrix: Out of dimension of ligne\n");
				return;
			}
		}

		for(int i=0; i<colone; i++){
			if(i < matrix_total_ligne(mat, ligne)){
				matrix_set(mat, ligne, i, v + i);
			}else{
				matrix_add_duplicate(mat, ligne, v + i);
			}
		}
	}
}

void matrix_multiple_vector(matrix * mat, vector * v, vector * newV){
	vector_init(newV, vector_total(v));
	int ligne = matrix_get_ligne(mat);
	int colone = matrix_get_colone(mat);

	if(colone != vector_total(v)){
		printf("Not same dimension of matrix and vector");
	}else{
		void * item;
		item = xmp_malloc(xmp_desc_of(item), vector_total(v));
		for(int i=0; i<ligne; i++){
			*(double *)(item + i) = 0;
			for(int j=0; j<colone; j++){
				*(double *)(items + i) += (*(double *)matrix_get(mat, i, j)) * (*(double *)vector_get(v, j));
			}
		}
		for(int i=0; i<ligne; i++){
			vector_add_duplicate(newV, items + i);
		}
		free(items);
		items = NULL;
	}	
}
//mat2 is a transpose of matrix
void matrix_multiple_matrix(matrix * mat1, matrix * mat2, matrix * newMat){
	vector v1, v2;
	matrix m;
	matrix_init(&m, matrix_get_ligne(mat1), matrix_get_ligne(mat2));
	for(int i=0; i<matrix_get_ligne(mat2); i++){
		matrix_get_vector(mat2, &v1, i);
		matrix_multiple_vector(mat1, &v1, &v2);
		stock_vector_in_matrix(&m, &v2, i);
		vector_free(&v1);
		vector_free(&v2);
	}
	matrix_transpose(&m, newMat);
	matrix_free(&m);
}

void upper_triangle_matrix_inverse(matrix * mat, matrix * mati){
	void * item;
	matrix_init(mati, matrix_get_ligne(mat), matrix_get_colone(mat));
	matrix_complete_ligne(mati);
	for(int k=0; k<matrix_get_ligne(mati); k++){
		item = xmp_malloc(xmp_desc_of(item), 1);
		if(*(double *)matrix_get(mat, k, k) == 0){
			printf("Matrix is not inversable!!!\n");
			exit(1);
		}else{
			*(double *)item = 1 / (*(double *)matrix_get(mat, k, k));
			matrix_set(mati, k, k, item);
		}
		free(item);
		if(k > 0){
			for(int j=k-1; j>=0; j--){
				item = xmp_malloc(xmp_desc_of(item), 1);
				*(double *)item = 0;
				for(int i=j+1; i<=k; i++){
					*(double *)item -= (*(double *)matrix_get(mat, j, i)) * (*(double *)matrix_get(mati, i, k)); 
				}
				if(*(double *)matrix_get(mat, j, j) == 0){
					printf("Matrix is not inversable!!!\n");
					exit(1);
				}else{
					*(double *)item = (*(double *)item) / (*(double *)matrix_get(mat, j, j));
					matrix_set(mati, j, k, item);
				}
				free(item);
			}
		}
	}
	item = NULL;
}

/******************
Matrix Ellpack
*******************/
#include <xmp.h>
void matrix_ell_multiple_vector(matrix_ELL * mat, vector * v, vector * newV){
	vector_init(newV, vector_total(v));
	void ** items_newV = xmp_malloc(sizeof(void *), vector_total(v));

	#pragma xmp nodes p(mat->ligne)
	#pragma xmp template(0:mat->ligne-1) 
	#pragma xmp distribute t(block) onto p
    #pragma xmp align mat->items[i][*] with t(i)
	#pragma xmp bcast (v)

	double index;
	if(mat->n_colone != vector_total(v)){
		printf("Not same dimension of matrix and vector");
	}else{
		double * items;
		items = xmp_malloc(xmp_desc_of(items), mat->ligne);
		#pragma xmp align items[i] with t[i]
		#pragma xmp loop on t[i]
		for(int i=0; i<mat->ligne; i++){
			*(items + i) = 0;
			for(int j=0; j<mat->colone/2; j++){
				index = *(double *)matrix_ell_get(mat, i, j);
				if(index != (double)(-1)){
					*(items + i) += (*(double *)matrix_ell_get(mat, i, mat->colone/2 + j)) * (*(double *)vector_get(v, index));
				}	
			}
		}
		#pragma xmp loop on t[i]
		for(int i=0; i<mat->ligne; i++){
			*(items_newV + i) = (void *)(items + i);
		}

		newV->items = items_newV;
		free(items);
		items = NULL;
	}	
}

//mat2 is a transpose of matrix
void matrix_ell_multiple_matrix(matrix_ELL * mat1, matrix * mat2, matrix * newMat){
	vector v1, v2;
	matrix m;
	matrix_init(&m, matrix_ell_get_ligne(mat1), matrix_get_ligne(mat2));
	for(int i=0; i<matrix_get_ligne(mat2); i++){
		matrix_get_vector(mat2, &v1, i);
		matrix_ell_multiple_vector(mat1, &v1, &v2);
		stock_vector_in_matrix(&m, &v2, i);
		vector_free(&v1);
		vector_free(&v2);
	}
	matrix_transpose(&m, newMat);
	matrix_free(&m);
}

void matrix_convert_matrix_ell(matrix * mat, matrix_ELL * matell){
	void * item;
	int * count, * index;
	int k;
	count = xmp_malloc(xmp_desc_of(count), 1);
	index = xmp_malloc(xmp_desc_of(index), 1);

	* count = 0;
	for(int i=0; i<mat->ligne; i++){
		* index = 0;
		for(int j=0; j<mat->colone; j++){
			if(*(double *)matrix_get(mat, i, j) != 0){
				* index = * index + 1;
			}
		}
		if(* index > * count){
			* count = * index;
		}
	}
	free(index); index = NULL;

	matrix_ell_init(matell, mat->ligne, 2 * (* count), mat->colone);

	for(int i=0; i<mat->ligne; i++){
		k = 0;
		for(int j=0; j<mat->colone; j++){
			if(*(double *)matrix_get(mat, i, j) != 0){
				item = xmp_malloc(xmp_desc_of(item), 1);
				*(double *)item = (double)j;
				matrix_ell_add_duplicate(matell, i, k, item);
				matrix_ell_add_duplicate(matell, i, (* count) + k, matrix_get(mat, i, j));
				k++;
				free(item); item = NULL;
			}
		}
	}
	free(count); count = NULL;
	matrix_ell_complete_ligne(matell);
}