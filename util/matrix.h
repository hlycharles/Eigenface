#ifndef MATRIX_H
#define MATRIX_H

int **matrix_mult(int **matrix1, int r1, int c1, int **matrix2, int r2, int c2);
void matrix_mult_double_rev(double *v1, int c, int *v2, int r, double *result);
double *matrix_mult_cplx(int **m, int r1, int c1, double *v, int r2);
void matrix_mult_cplx_rev(double *m, int c, int *v, int r, double *real, double *img);
int **matrix_transpose(int **matrix, int r, int c);
int vec_dist(double *v1, double *v2, int len);

void free_matrix(int **m, int r);

#endif
