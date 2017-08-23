#include <stdio.h>
#include <stdlib.h>
#include <xmp.h>
#include "vector_xmp.h"

int vector_total(vector * v){
	return v->total;
}

int vector_length(vector * v){
	return v->capacity;
}

double * vector_items(vector * v){
	return v->items;
}

void vector_init(vector * v, int length){
	v->capacity = length;
	v->total = 0;
	v->items = xmp_malloc(xmp_desc_of(v->items), length);
}

void vector_add(vector * v, double item){
	if(v->capacity == v->total){
		printf("Vector: Out of dimension");
	}
	v->items[v->total++] = item;
}

void vector_add_duplicate(vector * v, double item){
	double item_dup;
	if(v->capacity == v->total){
		printf("Vector: Out of dimension");
	}
	item_dup = item;
	v->items[v->total++] = item_dup;
}

void vector_set(vector * v, int index, double item){
	if(index >= 0 && index < v->total){
		v->items[index] = item;
	}
}

double vector_get(vector * v, int index){
	if(index >= 0 && index < v->total){
		return v->items[index];
	}else{
		return NULL;
	}
}

void vector_delete(vector * v, int index){
	if(index >= 0 && index < v->total){
		for(int i = index; i < v->total - 1; i++){
			v->items[i] = v->items[i + 1];
		}

		v->total--;
	}else{
		printf("No more element in vector!!!\n");
		return;
	}
}

void vector_free(vector * v){
	v->capacity = 0;
	v->total = 0;
	free(v->items);
	v->items = NULL;
}

void vector_show(vector * v){
	for(int i=0; i<vector_total(v); i++){
		printf("%f ", vector_get(v, i));
	}
	printf("\n");
}

void vector_copy(vector * v, vector * newV){
	vector_init(newV, vector_length(v));

	for(int i=0; i<v->total; i++){
		vector_add(newV, vector_get(v, i));
	}
}

void vector_duplicate(vector * v, vector * newV){
	vector_init(newV, vector_length(v));

	for(int i=0; i<v->total; i++){
		vector_add_duplicate(newV, vector_get(v, i));
	}
}