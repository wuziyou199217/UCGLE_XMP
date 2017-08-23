#ifndef VECTOR_H
#define VECTOR_H

#define VECTOR_INIT(vec, length) vector_init(&vec, length)
#define VECTOR_ADD(vec, item) vector_add(&vec, item)
#define VECTOR_ADD_DUPLICATE(vec, item) vector_add_duplicate(&vec, item)
#define VECTOR_SET(vec, id, item) vector_set(&vec, id, item)
#define VECTOR_GET(vec, type, id) (type) vector_get(&vec, id)
#define VECTOR_DELETE(vec, id) vector_delete(&vec, id)
#define VECTOR_LENGTH(vec) vector_length(&vec)
#define VECTOR_TOTAL(vec) vector_total(&vec)
#define VECTOR_ITEMS(vec) vector_items(&vec)
#define VECTOR_FREE(vec) vector_free(&vec)
#define VECTOR_SHOW(vec) vector_show(&vec)
#define VECTOR_COPY(vec1, vec2) vector_copy(&vec1, &vec2)
#define VECTOR_DUPLICATE(vec1, vec2) vector_duplicate(&vec1, &vec2)

typedef struct vector {
	double * items;
	int capacity;
	int total;
} vector;

void vector_init(vector * v, int length);
int vector_length(vector * v);
int vector_total(vector * v);
double * vector_items(vector * v);
void vector_add(vector * v, double item);
void vector_add_duplicate(vector * v, double item);
void vector_set(vector * v, int index, double item);
double vector_get(vector * v, int index);
void vector_delete(vector * v, int index);
void vector_free(vector * v);
void vector_show(vector * v);
void vector_copy(vector * v, vector * newV);
void vector_duplicate(vector * v, vector * newV);

#endif