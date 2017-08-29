#include <stdio.h>
#include <stdlib.h>
#include <xmp>
#include "arnoldi_gmres.h"

matrix mat;

//prefunction to initialize mat, mat_ell and V
void startPreparation (void) __attribute__((constructor));
void startPreparation(){}