
CC=gcc

all: train

train: ../params.c ../util/io.c ../util/matrix.c ../util/eigen.c train.c
	$(CC) -I/usr/local/Cellar/gsl/2.4/include -L/usr/local/Cellar/gsl/2.4/lib ../params.c ../util/io.c ../util/matrix.c ../util/eigen.c train.c -o build/train -lgsl -lgslcblas -lm
