#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mVecMatrix.h"

int main(void){
	int i;
	double item = 5;
	double a = 2.38, b = 7.65, c = 8.34, d = 105;

	vector v;
	vector_init(&v);

	vector_add(&v, &a);
	vector_add(&v, &b);
	vector_add(&v, &c);
	vector_add(&v, &d);

	for(i=0; i<vector_total(&v); i++){
		printf("%f ", *(double *)vector_get(&v, i));
	}
	printf("\n");

	vector_divid(&v, item);

	for(i=0; i<vector_total(&v); i++){
		printf("%f ", *(double *)vector_get(&v, i));
	}
	printf("\n");
}