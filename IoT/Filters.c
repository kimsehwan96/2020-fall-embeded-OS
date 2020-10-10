float LowPassFilter(float tau,float ts, float pre_y, float x){
    return (tau * pre_y + ts * x) / (tau + ts);
    // tau는 시정수
    // ts는 샘플링 타임
    // pre_y는 이전 결과 값
    // x는 현재 input.
    // 그냥 이케 구현하는게 맞나???
}

void HighPassFilter(float tau,float ts, float pre_x, float pre_y, float x){
    return tau/(tau + ts) * pre_y + tau / (tau + ts) * (x - pre_x);
    // tau -> 시정수
    // ts 샘플링 타임
    // pre_x 이전 입력값
    // pre_y 이전 결과 값
    // x 현재 입력값.
}

void BandWidthFilter(){
    // 구현 해야 함.
}