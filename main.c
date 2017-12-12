#include <stdio.h>

#include "./recognition.h"
#include "./resample/resample.h"
#include "./params.h"
#include "./util/io.h"

void outputFaceIndex(int faceIndex) {
	printf("face index: %d\n", faceIndex);
}

int main() {
	// read input image size
	int imgSizes[2];
	readInts("../data/input_size.txt", 2, imgSizes);
	int imgR = imgSizes[0];
	int imgC = imgSizes[1];

	// read input image
	int inputImg[imgR * imgC];
	readImg(imgR, imgC, "../data/input.txt", inputImg);

	// resample input image
	int resizedInput[imgLen];
	resample(imgR, imgC, inputImg, resizedInput);

	// read training set size
	int trainingSetSize = readInt("../data/training_count.txt");
	int faceIndex = recognizeImage(resizedInput);

	// output result
	outputFaceIndex(faceIndex);

	return 0;
}
