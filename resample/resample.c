#include <stdio.h>
#include <math.h>

const int dimension = 20;

void resample(int sr, int sc, int src[], int dest[]) {
    // currently ignore images whose one dimension is less than 20
    if (sr < dimension || sc < dimension) {
        return;
    }

    double hScale = (double)sc / dimension;
    double vScale = (double)sr / dimension;

    int i = 0;
    double currentVScale = vScale;
    int desti = 0;
    while (i < sr && desti < dimension) {
// #pragma HLS LOOP_TRIPCOUNT min=20 max=20
        int vStride = (int)floor(currentVScale);
        if (desti == dimension - 1) {
            vStride = sr - i;
        }
        int j = 0;
        double currentHScale = hScale;
        int destj = 0;
        while (j < sc && destj < dimension) {
// #pragma HLS LOOP_TRIPCOUNT min=20 max=20
            int hStride = (int)floor(currentHScale);
            if (destj == dimension - 1) {
                hStride = sc - j;
            }
            int currentSum = 0;
            for (int k = i; k < i + vStride && k < sr; k++) {
// #pragma HLS LOOP_TRIPCOUNT min=1 max=9
                for (int l = j; l < j + hStride && l < sc; l++) {
// #pragma HLS LOOP_TRIPCOUNT min=1 max=12
                    currentSum += src[k * sc + l];
                }
            }
            int avg = currentSum / (vStride * hStride);
            dest[desti * dimension + destj] = avg;
            destj++;
            j += hStride;
            currentHScale -= (double)hStride;
            currentHScale += hScale;
        }
        desti++;
        i += vStride;
        currentVScale -= (double)vStride;
        currentVScale += vScale;
    }
}
