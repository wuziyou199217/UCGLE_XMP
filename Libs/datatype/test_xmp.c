#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <xmp.h>

#pragma xmp nodes p(NPES)
#pragma xmp template t(0:ROWS_NUM-1)
#pragma xmp distribute t(block) onto p

//matrix and vector for parallel computing
double mat[ROWS_NUM][COLS_NUM];
double V[ROWS_NUM];
#pragma xmp align mat[i][*] with t(i)
#pragma xmp align V[i] with t(i)

//function which aide the routine
void initialize(int index, int count);

//main function
int main(void){
	int index, count;

	initialize(index, count);
}

void initialize(int index, int count){
	index = 0;
	count = 3;
	printf("index: %d, count: %d\n", index, count);

	#pragma xmp loop on t(i)
{
	for(int i=0; i<ROWS_NUM; i++){
		for(int j=0; j<COLS_NUM; j++){
			mat[i][j] = 2.1;
		}
	}
}

	#pragma xmp loop on t(i)
{
	for(int i=0; i<ROWS_NUM; i++){
		V[i] = 1;
	}
}
}