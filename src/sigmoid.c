// returns e ^ x
float myexp(float x) {
    // calculated using taylors expansion
    if(x < 0) return (1.0 / myexp(-x));

    int order = 7;

    float fact = 1;
    float pow_x = 1;
    float res = 1;

    for(int i = 1; i <= order; i++) {
        fact *= i;
        pow_x *= x;

        res += pow_x / fact;
    }

    return res;
}

float sigmoid(float x) {
    return 1.0 / (1.0 + myexp(-x));
}

float sigmoid_deriv(float x) {
    return sigmoid(x) * (1.0 - sigmoid(x));
}
