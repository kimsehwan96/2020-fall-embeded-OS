#include <stdio.h>

float LowPassFilter(float tau,float ts, float pre_y, float x){
    return (tau * pre_y + ts * x) / (tau + ts);
    // tau는 시정수
    // ts는 샘플링 타임
    // pre_y는 이전 결과 값
    // x는 현재 input.
}

void main() {
    float tau = 10.0;
    float ts = 1000.0;
    float inputArr[5] = {10.0, 20.0, 30.0 ,5.32, 6.32};
    float result_y[5] = {};
    float tmp = 0;
    for(int i = 0; i<=5; i++){
        if (i == 0){
        result_y[i] =LowPassFilter(tau, ts, 0, inputArr[i]);
        }
        else {
            result_y[i] = LowPassFilter(tau, ts, result_y[i-1], inputArr[i]);
        }
    }

    for(int i = 0; i <=5; i++){
        tmp = result_y[i];
        printf("%f", tmp);
    }
}