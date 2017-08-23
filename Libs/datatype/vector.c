#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

int vector_capacity(vector * v){
	return v->capacity;
}

int vector_total(vector * v){
	return v->total;
}

void ** vector_items(vector * v){
	return v->items;
}

void vector_init(vector * v, int capacity){
	v->capacity = capacity;
	v->total = 0;
	v->items = malloc(sizeof(void *) * v->capacity);
}

void vector_add(vector * v, void * item){
	if(v->capacity == v->total){
		printf("Vector: Out of dimension");
	}
	v->items[v->total++] = item;
}

void vector_add_duplicate(vector * v, void * item){
	double * item_dup = (double *)malloc(sizeof(double));
	if(v->capacity == v->total){
		printf("Vector: Out of dimension");
	}
	* item_dup = *(double *)item;
	v->items[v->total++] = (void *)item_dup;
}

void vector_set(vector * v, int index, void * item){
	if(index >= 0 && index < v->total){
		*(double *)v->items[index] = *(double *)item;
	}
}

void * vector_get(vector * v, int index){
	if(index >= 0 && index < v->total){
		return v->items[index];
	}
	return NULL;
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
		printf("%0.15f ", *(double *)vector_get(v, i));
	}
	printf("\n");
}

void vector_copy(vector * v, vector * newV){
	vector_init(newV, vector_capacity(v));

	for(int i=0; i<v->total; i++){
		vector_add(newV, vector_get(v, i));
	}
}

void vector_duplicate(vector * v, vector * newV){
	vector_init(newV, vector_capacity(v));

	for(int i=0; i<v->total; i++){
		vector_add_duplicate(newV, vector_get(v, i));
	}
}