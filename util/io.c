#include <stdlib.h>
#include <stdio.h>

int readInt(char path[]) {
    FILE *fp;
    fp = fopen(path, "r");
    int result;
    fscanf(fp, "%d", &result);
    fclose(fp);
    return result;
}

void readInts(char path[], int count, int dest[]) {
    FILE *fp;
    fp = fopen(path, "r");
    int result;
    for (int i = 0; i < count; i++) {
        fscanf(fp, "%d", &result);
        dest[i] = result;
    }
    fclose(fp);
}

int **readImgs(int imgSize, int imgSetSize, char *imgPath) {
    FILE *fp;
    fp = fopen(imgPath, "r");
    int val;
    int **result = malloc(sizeof(int *) * imgSetSize);
    for (int i = 0; i < imgSetSize; i++) {
        result[i] = malloc(sizeof(int) * imgSize * imgSize);
        for (int j = 0; j < imgSize * imgSize; j++) {
            fscanf(fp, "%d", &val);
            result[i][j] = val;
        }
    }
    fclose(fp);
    return result;
}

void readImg(int r, int c, char path[], int dest[]) {
    FILE *fp;
    fp = fopen(path, "r");
    for (int i = 0; i < r * c; i++) {
        int val;
        fscanf(fp, "%d", &val);
        dest[i] = val;
    }
    fclose(fp);
}

void readCplxMatrix(int r, int c, char path[], double dest[][c]) {
    FILE *fp;
    fp = fopen(path, "r");
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            double val;
            fscanf(fp, "%lf", &val);
            dest[i][j] = val;
        }
    }
}

void storeVec(int *v, int size, char path[]) {
    FILE *fp;
    fp = fopen(path, "w");
    for (int i = 0; i < size; i++) {
        fprintf(fp, "%d\n", v[i]);
    }
    fclose(fp);
}

void storeVec_double(double *v, int size, char path[]) {
    FILE *fp;
    fp = fopen(path, "w");
    for (int i = 0; i < size * 2; i++) {
        fprintf(fp, "%.3f\n", v[i]);
    }
    fclose(fp);
}

void storeMatrix_double(double **m, int r, int c, char path[]) {
    FILE *fp;
    fp = fopen(path, "w");
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            // only store real part of the result
            fprintf(fp, "%.3f\n", m[i][j * 2]);
        } 
    }
    fclose(fp);
}
