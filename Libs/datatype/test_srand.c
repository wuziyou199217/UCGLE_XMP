#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "constant_data.h"



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
			printf("%d ", mat[i][j]);
		}
	}
	printf("\n");
}