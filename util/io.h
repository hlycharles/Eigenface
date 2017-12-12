#ifndef IO_H
#define IO_H

int readInt(char path[]);
void readInts(char path[], int count, int dest[]);
void readImg(int r, int c, char path[], int dest[]);
int **readImgs(int imgSize, int imgSetSize, char *imgPath);

void readCplxMatrix(int r, int c, char path[], double dest[][c*2]);

void storeVec(int *v, int size, char path[]);
void storeVec_double(double *v, int size, char path[]);
void storeMatrix_double(double **m, int r, int c, char path[]);

#endif
