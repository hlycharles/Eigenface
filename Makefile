
CC=gcc

all: main

main: ./params.c util/matrix.c util/io.c recognition.c ./resample/resample.c main.c
	$(CC) ./params.c util/matrix.c util/io.c recognition.c ./resample/resample.c main.c -o build/main -lm
