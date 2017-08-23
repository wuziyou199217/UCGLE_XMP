#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "constant_data.h"

double mat[ROWS_NUM][COLS_NUM];

//readMatrix
void readMatrix (void) __attribute__ ((constructor)); 

void readMatrix (void)
{
	FILE * f1;
	double * temp = malloc(sizeof(double));

	f1 = fopen("mat_sample.txt", "rb");
	for(int i=0; i<ROWS_NUM; i++){
		for(int j=0; j<COLS_NUM; j++){
			fread(temp, sizeof(double), 1, f1);
			mat[i][j] = * temp;
		}
	}
}

int main(void){
	for(int i=0; i<ROWS_NUM; i++){
		for(int j=0; j<COLS_NUM; j++){
			printf("%f ", mat[i][j]);
		}
		printf("\n");
	}
}