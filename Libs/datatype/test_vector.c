#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

int main(void){
	double a = 3.24, b = 7.65, c = 8.34, d = 105, e = 78.3, f = 3.6;

	vector v;
	vector newV;
	vector_init(&v, 6);

	vector_add(&v, &a);
	vector_add(&v, &b);
	vector_add(&v, &c);
	vector_add(&v, &d);
	vector_add(&v, &e);
	vector_duplicate(&v, &newV);
	vector_show(&v);
	vector_show(&newV);

	vector_delete(&newV, 3);

	vector_set(&newV, 0, &f);
	vector_show(&newV);

	b = 7.8; d = 6.666;
	vector_show(&v);
	vector_show(&newV);


	vector_free(&v);
	vector_free(&newV);
}
