#include <stdio.h>

float HighPassFilter(float tau,float ts, float pre_x, float pre_y, float x){
    return tau/(tau + ts) * pre_y + tau / (tau + ts) * (x - pre_x);
}


void main() {
    float tau = 10.0;
    float ts = 1000.0;
    float inputArr[5] = {10.0, 20.0, 30.0 ,5.32, 6.32};
    float result_y[5] = {};
    float tmp = 0;
    for(int i = 0; i<=5; i++){
        if (i == 0){
        result_y[i] = HighPassFilter(tau, ts, 0, 0, inputArr[i]);
        }
        else {
            result_y[i] = HighPassFilter(tau, ts, inputArr[i-1], result_y[i-1], inputArr[i]);
        }
    }

    for(int i = 0; i <=5; i++){
        tmp = result_y[i];
        printf("%f", tmp);
    }
}