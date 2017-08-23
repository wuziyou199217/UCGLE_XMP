#include <datatype/vector.h>
#include <datatype/matrix.h>

#ifndef MVECMATRIX_H
#define MVECMATRIX_H

#define VECTOR_DIVID(vec, x) vector_divid(&vec, x)
#define MATRIX_MULTIPLE_VECTOR(mat, vec) matrix_multiple_vector(&mat, &vec)
#define VECTOR_INNER_PRODUIT(vec1, vec2) vector_inner_produit(&vec1, &vec2)
#define VECTOR_ABS(vec) vector_abs(&vec)

vector vector_divid(vector * v, double x);
vector matrix_multiple_vector(matrix * mat, vector * v);
double vector_inner_produit(vector * v1, vector * v2);
double vector_abs(vector * v);

#endif