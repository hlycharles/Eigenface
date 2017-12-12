#include <stdlib.h>
#include <stdio.h>

#include "../params.h"
#include "../util/matrix.h"
#include "../util/eigen.h"
#include "../util/io.h"

int imgSetSize;

int **imgs;

int *calculateAvgImg() {
    int *avgImg = malloc(imgSize * imgSize * sizeof(int));
    // init average image
    for (int i = 0; i < imgSize * imgSize; i++) {
        avgImg[i] = 0;
    }
    // calculate aggregate sum for each pixel
    for (int c = 0; c < imgSetSize; c++) {
        int *img = imgs[c];
        for (int i = 0; i < imgSize * imgSize; i++) {
            avgImg[i] += img[i];
        }
    }
    // calculate average value for each pixel
    for (int i = 0; i < imgSize * imgSize; i++) {
        avgImg[i] /= imgSetSize;
    }

    storeVec(avgImg, imgSize * imgSize, "../../models/avg.txt");
    return avgImg;
}

void calculateEigenElems(int *avgImg) {
    int **normalized = malloc(imgSetSize * sizeof(int *));
    for (int i = 0; i < imgSetSize; i++) {
        normalized[i] = malloc(imgSize * imgSize * sizeof(int));
        for (int j = 0; j < imgSize * imgSize; j++) {
            normalized[i][j] = imgs[i][j] - avgImg[j];
        }
    }
    // preprocess matrices
    int imgLen = imgSize * imgSize;
    int **normal_trans = matrix_transpose(normalized, imgSetSize, imgLen);
    int **normal_mult = matrix_mult(
        normalized, imgSetSize, imgLen, normal_trans, imgLen, imgSetSize
    );
    // calculate eigen elements
    double *eval = malloc(sizeof(double) * imgSetSize * 2);
    double **evec = malloc(sizeof(double) * imgSetSize);
    for (int i = 0; i < imgSetSize; i++) {
        evec[i] = malloc(sizeof(double) * imgSetSize * 2);
        for (int j = 0; j < imgSetSize * 2; j++) {
            evec[i][j] = 0;
        }
    }
    eigen_system((int **)normal_mult, imgSetSize, eval, evec);

    double **ws = malloc(sizeof(double *) * imgSetSize);
    double **vecs = malloc(sizeof(double *) * imgSetSize);
    for (int i = 0; i < imgSetSize; i++) {
        ws[i] = malloc(sizeof(double) * imgSetSize * 2);
        vecs[i] = malloc(sizeof(double) * imgLen * 2);
    }
    for (int i = 0; i < imgSetSize; i++) {
        double *final_vec = matrix_mult_cplx(normal_trans, imgLen, imgSetSize, evec[i], imgSetSize * 2);
        for (int j = 0; j < imgLen * 2; j++) {
            vecs[i][j] = final_vec[j];
        }
        for (int k = 0; k < imgSetSize; k++) {
            double real, img;
            matrix_mult_cplx_rev(final_vec, imgLen, normalized[k], imgLen, &real, &img);
            ws[k][2 * i] = real;
            ws[k][2 * i + 1] = img;
        }
        free(final_vec);
    }
    storeMatrix_double(ws, imgSetSize, imgSetSize, "../../models/eval.txt");
    storeMatrix_double(vecs, imgSetSize, imgLen, "../../models/evec.txt");

    free_matrix(normalized, imgSetSize);
    free_matrix(normal_trans, imgLen);
    free_matrix(normal_mult, imgSetSize);

    free(eval);
    free(evec);
    free(ws);
    free(vecs);
 }

int main() {

    imgSetSize = readInt("../../data/training_count.txt");
    printf("training with %d images\n", imgSetSize);

    printf("reading %d images\n", imgSetSize);
    imgs = readImgs(imgSize, imgSetSize, "../../data/training_images.txt");

    printf("Calculating average image...\n");
    int *avg = calculateAvgImg(); 

    printf("Calculating eigen elements...\n");
    calculateEigenElems(avg);

    printf("Done training\n");

    printf("Freeing images\n");
    for (int i = 0; i < imgSetSize; i++) {
        free(imgs[i]);
    }
    free(imgs);

    printf("Done\n");

    free(avg);
    return 0;
}
