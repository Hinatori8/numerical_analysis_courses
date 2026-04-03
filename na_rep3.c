#include <stdio.h>
#include <math.h>
#include <unistd.h>
void print_report(int n, double a, double b);
void print_result(int n, double x, double residual);
#define Tol_range 1e-12

/*非線形方程式f(x)*/
double func(double x) {
    return ((x - 2.0) * x - 1.0) * x + 2.0;
}

/*二分法の処理関数*/
void bisection_method(double a, double b) {
    int i = 0;
    double fa = func(a);

    while (fabs(b - a) >= Tol_range) {
        i++;
        double c  = (a + b) / 2.0;
        double fc = func(c);

        if (fa * fc > 0.0) {
            a  = c;
            fa = fc;
        } else if (fa * fc < 0.0) {
            b = c;
        } else {
            print_result(i, c, fabs(fc));
            return;
        }
        print_report(i, a, b);
    }

    print_result(i, a, fabs(func(a)));
}

int main(void) {
    double a = 1.5;
    double b = 3.0;

    printf("初期区間: [%.16f, %.16f]\n", a, b);
    printf("***二分法を実行***\n\n");

    bisection_method(a, b);

    return 0;
}

/* 出力 */
void print_report(int n, double a, double b) {
    printf("%2d反復後の区間: [%.16f, %.16f]\n", n, a, b);
    usleep(100000);
}

void print_result(int n, double x, double residual) {
    printf("\n***計算結果***\n");
    usleep(500000);
    printf("反復回数: %d\n", n);
    printf("近似解  : %.16f\n", x);
    printf("残差    : %.2e\n", residual);
}
