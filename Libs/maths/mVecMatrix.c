#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mVecMatrix.h"

vector vector_divid(vector * v, double x){
	for(int i=0; i<v->total; i++){
		double item = (*(double *)vector_get(v, i))/x;
		vector_set(v, i, &item);
	}
}

