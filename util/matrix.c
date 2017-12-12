#include <stdlib.h>
#include <math.h>

int **matrix_transpose(int **matrix, int r, int c) {
    int **result = malloc(sizeof(int *) * c);
    for (int j = 0; j < c; j++) {
        result[j] = malloc(r * sizeof(int));
        for (int i = 0; i < r; i++) {
            result[j][i] = matrix[i][j];
        }
    }
    return result;
}

int **matrix_mult(int **matrix1, int r1, int c1, int **matrix2, int r2, int c2) {
    if (c1 != r2) {
        return NULL;
    }
    int **result = malloc(sizeof(int *) * r1);
    for (int i = 0; i < r1; i++) {
        result[i] = malloc(c2 * sizeof(int));
        for (int j = 0; j < c2; j++) {
            int sum = 0;
            for (int k = 0; k < c1; k++) {
                sum += matrix1[i][k] * matrix2[k][j];
            }
            result[i][j] = sum;
        }
    }
    return result;
}

void matrix_mult_double_rev(double *v1, int c, int *v2, int r, double *result) {
    if (c != r) {
        return;
    }
    double total = 0;
    for (int i = 0; i < c; i++) {
        total += v1[i] * v2[i];
    }
    *result = total;
}

double *matrix_mult_cplx(int **m, int r1, int c1, double *v, int r2) {
    if (c1 * 2 != r2) {
        return NULL;
    }
    double *result = malloc(sizeof(double) * r1 * 2);
    for (int i = 0; i < r1; i++) {
        double real = 0;
        double img = 0;
        for (int j = 0; j < c1; j++) {
            real += m[i][j] * v[2 * j];
            img += m[i][j] * v[2 * j + 1];
        }
        result[2 * i] = real;
        result[2 * i + 1] = img;
    }
    return result;
}

void matrix_mult_cplx_rev(
    double *v1, int c, int *v2, int r, double *real, double *img
) {
    if (c != r) {
        return;
    }
    double realVal = 0;
    double imgVal = 0;
    for (int i = 0; i < c; i++) {
        realVal += v1[2 * i] * v2[i];
        imgVal += v1[2 * i + 1] * v2[i];
    }
    *real = realVal;
    *img = imgVal;
}

// calculate Euclidean distance between two vectors
int vec_dist(double *v1, double *v2, int len) {
    double result = 0;
    for (int i = 0; i < len; i++) {
        double diff = v1[i] - v2[i];
        result += diff * diff;
    }
    return (int)(sqrt(result));
}

// free matrix
void free_matrix(int **m, int r) {
    for (int i = 0; i < r; i++) {
        free(m[i]);
    }
    free(m);
}
