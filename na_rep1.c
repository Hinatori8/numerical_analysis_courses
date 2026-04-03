#include <stdio.h>
#include <unistd.h>
#include <math.h>

#define OUTPUT_LIMIT 1000

void func(double x, double *y){
     *y = 1.0 + 1.0 / x;
}

void print_iter(int k, double x_k) {
    printf("k=%2d, x_k = %.16f\n", k, x_k);
}

void print_convergence(double value) {
    printf("\nx_kは%.16fに収束する（有効数字17桁切り捨ての場合）\n", value);
}

int main(void) {
    double x_k = 1.0;
    double result[OUTPUT_LIMIT] = {0};

    for (int i = 0; ; i++) {
        print_iter(i, x_k);

        func(x_k, result + i);
        x_k = result[i];

        if (i > 1) {
            if (result[i - 1] == result[i]) {
                print_convergence(result[i]);
                break;
            }
            if (i == OUTPUT_LIMIT) {
                printf("出力上限に達しました\n");
                break;
            }
        }
        usleep(100000);
    }

    return 0;
}
