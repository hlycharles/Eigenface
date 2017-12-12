#include <gsl/gsl_eigen.h>

void eigen_system(int **matrix, int size, double *eva, double **eve) {
    gsl_eigen_nonsymmv_workspace *w = gsl_eigen_nonsymmv_alloc(size);
    gsl_matrix *m = gsl_matrix_alloc(size, size);
    // populate gsl matrix
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            gsl_matrix_set(m, i, j, matrix[i][j]);
        }
    }
    gsl_vector_complex *eval = gsl_vector_complex_calloc(size);
    gsl_matrix_complex *evec = gsl_matrix_complex_calloc(size, size);
    gsl_eigen_nonsymmv(m, eval, evec, w);

    if (eva != NULL) {
        for (int i = 0; i < size; i++) {
            eva[2 * i] = GSL_VECTOR_REAL(eval, i);
            eva[2 * i + 1] = GSL_VECTOR_IMAG(eval, i);
        }
    }

    if (eve != NULL) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                eve[i][2 * j] = GSL_REAL(gsl_matrix_complex_get(evec, j, i));
                eve[i][2 * j + 1] = GSL_IMAG(gsl_matrix_complex_get(evec, j, i));
            }
        }
    }

    // free memory
    gsl_eigen_nonsymmv_free(w);
    gsl_matrix_free(m);
    gsl_vector_complex_free(eval);
    gsl_matrix_complex_free(evec);
}
