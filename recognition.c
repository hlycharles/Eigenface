#include "util/matrix.h"
#include "util/io.h"
#include "./params.h"

int imgSetSize;

void calcWeightVectorElem(double *evec, int *normalized, double *dist) {
    matrix_mult_double_rev(evec, imgLen, normalized, imgLen, dist);
}

int findFaceIndex(double *wvec, double wvecs[][imgSetSize]) {
    int index = -1;
    int minDist = -1;
    for (int i = 0; i < imgSetSize; i++) {
        double *currVec = wvecs[i];
        int dist = vec_dist(wvec, currVec, imgSetSize);
        if (minDist < 0 || dist < minDist) {
            minDist = dist;
            index = i;
        }
    }

    return index;
}

// return index of person recognized, -1 if not a person
int recognizeImage(int inputImg[]) {
    // read training image set size
    imgSetSize = readInt("../data/training_count.txt");

    // read average image
    int avgImg[imgLen];
    readImg(imgSize, imgSize, "../models/avg.txt", avgImg);

    // read eigenvectors
    double evecs[imgSetSize][imgLen];
    readCplxMatrix(imgSetSize, imgLen, "../models/evec.txt", evecs);

    // read weight vectors
    double wvecs[imgSetSize][imgSetSize];
    readCplxMatrix(imgSetSize, imgSetSize, "../models/eval.txt", wvecs);

    // calculate normalized image
    int normalized[imgLen];
    int i, j;
    for (i = 0; i < imgLen; i++) {
        normalized[i] = inputImg[i] - avgImg[i];
    }

    // calculate weight vector
    double wvec[imgSetSize];
    for (j = 0; j < imgSetSize; j++) {
        double *evec = evecs[j];
        double dist;
        calcWeightVectorElem(evec, normalized, &dist);
        wvec[j] = dist;
    }

    // find the face index
    int faceIndex = findFaceIndex(wvec, wvecs);

    return faceIndex;
}
