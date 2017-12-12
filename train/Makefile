
CC=gcc
GSL=/usr/local/Cellar/gsl/2.4/

all: train

train: ../params.c ../util/io.c ../util/matrix.c ../util/eigen.c train.c
	$(CC) -I$(GSL)include -L/usr/local/Cellar/gsl/2.4/lib ../params.c ../util/io.c ../util/matrix.c ../util/eigen.c train.c -o build/train -lgsl -lgslcblas -lm
