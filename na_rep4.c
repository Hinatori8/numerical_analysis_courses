#include <stdio.h>
#include <math.h>
#include <unistd.h>

#define Ini_x       -6.0  // 初期値
#define Tol_range   1e-10 // 許容誤差
#define LOOP_LIMIT  300 // 最大反復回数
#define Exact_sol   0.5 // 厳密解
void print_report(int,double,double);
void print_result(int,double,double);

double func(double x) {
        return ((x - 4.0) * x + 13.0 / 4.0) * x - 3.0 / 4.0;
}

double func_deriv(double x) {
    return (3.0 * x - 8.0) * x + 13.0 / 4.0;
}

double newton_step(double x_k) {
    return x_k - func(x_k) / func_deriv(x_k);
}


void exe_newton(double x_k) {
    for (int i = 1; i <= LOOP_LIMIT; i++) {
        x_k = newton_step(x_k);
        print_report(i, x_k, fabs(Exact_sol - x_k));

        if (fabs(func(x_k)) <= Tol_range) {
            print_result(i, x_k, fabs(Exact_sol - x_k));
            return;
        }
    }

    printf("反復回数上限に到達\n");
    print_result(LOOP_LIMIT, x_k, fabs(Exact_sol - x_k));
}

int main(void) {
    printf("初期値: %.16f,  初期絶対誤差: %.2e\n", Ini_x, fabs(Ini_x- Exact_sol));
    printf("***ニュートン法を実行***\n\n");

    exe_newton(Ini_x);

    return 0;
}

/* 出力関数 */
void print_report(int n, double x, double err) {
    printf("  %3d: x = %.16f,  誤差 = %.2e\n", n, x, err);
    usleep(100000);
}

void print_result(int n, double x, double err) {
    printf("\n***計算結果***\n");
    usleep(500000);
    printf("反復回数: %2d\n", n);
    printf("近似解  : %.16f\n", x);
    printf("絶対誤差: %.2e\n", err);
}