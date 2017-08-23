#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "constant_data.h"

//random_get function
double random_get(double min, double max);
int matrix_max_count(double m[ROWS_NUM][COLS_NUM]);

//main function
int main(void){
	srand(time(NULL));
	double mat[ROWS_NUM][COLS_NUM];
	
	for(int i=0; i<ROWS_NUM; i++){
		for(int j=0; j<COLS_NUM; j++){
			if(j == i + 1 || j == i || j == i - 1){
				mat[i][j] = random_get(-10, 10);
			}else{
				mat[i][j] = 0;
			}
		}
	}
/**
	//write to mat_sample.txt
	FILE *f1;
	f1 = fopen("mat_sample3.txt", "wb+");
	int ret;
	for(int i=0; i<ROWS_NUM; i++){
		ret = fwrite(mat[i], sizeof(double), COLS_NUM, f1);
	}
	fclose(f1);
**/
	//matrix convert to matrix ellpack
	int count = 2 * matrix_max_count(mat);
	#define COLS_ELL_COUNT count
	double m_ell[ROWS_NUM][COLS_ELL_NUM];
	int k;

	//initialize matrix ellpack
	for(int i=0; i<ROWS_NUM; i++){
		for(int j=0; j<COLS_ELL_COUNT; j++){
			m_ell[i][j] = -1;
		}
	}

	//copy data from matrix
	for(int i=0; i<ROWS_NUM; i++){
		k = 0;
		for(int j=0; j<COLS_NUM; j++){
			if(mat[i][j] != 0){
				m_ell[i][k] = (double)j;
				m_ell[i][count/2 + k] = mat[i][j];
				k++;
			}
		}
	}
	
	for(int i=0; i<ROWS_NUM; i++){
		for(int j=0; j<COLS_ELL_COUNT; j++){
			printf("%f ", m_ell[i][j]);
		}
		printf("\n");
	}
/**
	//write to mat_ell_sample.txt
	FILE *f2;
	f2 = fopen("mat_ell_sample3.txt", "wb+");
	for(int i=0; i<ROWS_NUM; i++){
		ret = fwrite(m_ell[i], sizeof(double), 2 * count, f2);
	}
	fclose(f2);
**/
}

double random_get(double min, double max){
	double range = max - min;
	double div = RAND_MAX / range;
	return min + (rand() / div);
}

int matrix_max_count(double m[ROWS_NUM][COLS_NUM]){
	int * count, * index;
	count = malloc(sizeof(int));
	index = malloc(sizeof(int));

	* count = 0;
	for(int i=0; i<ROWS_NUM; i++){
		* index = 0;
		for(int j=0; j<COLS_NUM; j++){
			if(m[i][j] != 0){
				* index = * index + 1;
			}
		}
		if(* index > * count){
			* count = * index;
		}
	}
	free(index); index = NULL;
	return (* count);
}