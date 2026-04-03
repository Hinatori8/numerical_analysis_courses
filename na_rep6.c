#include <stdio.h>
#include <math.h>

#define N         20
#define Tol_range 1e-8
#define MAX_ITER  500
void print_system(const double (*A)[N], const double *b, int n);
void print_solution(const double *x, int n, int iter);

/* 行列の初期化*/
void ini_band_matrix(double (*A)[N], double *b, int n) {
    A[0][0] = 3.0;
    A[0][1] = 1.0;
    for (int i = 1; i < n - 1; i++) {
        A[i][i - 1] = 1.0;
        A[i][i]     = 3.0;
        A[i][i + 1] = 1.0;
    }
    A[n - 1][n - 2] = 1.0;
    A[n - 1][n - 1] = 3.0;

    for (int i = 0; i < n; i++)
        b[i] = (double)(i + 1);
}


/* ヤコビ法の実行関数 */
int jacobi_iteration(const double (*A)[N], const double *b, double *x, int n) {
    double x_new[N];

    for (int k = 1; k <= MAX_ITER; k++) {
        for (int i = 0; i < n; i++) {
            double sum = 0.0;
            for (int j = 0; j < n; j++) {
                if (j != i)
                    sum += A[i][j] * x[j];
            }
            x_new[i] = (b[i] - sum) / A[i][i];
        }

        double max_diff = 0.0, max_val = 0.0;
        for (int i = 0; i < n; i++) {
            double diff = fabs(x_new[i] - x[i]);
            double val  = fabs(x[i]);
            if (diff > max_diff) max_diff = diff;
            if (val  > max_val)  max_val  = val;
        }

        for (int i = 0; i < n; i++)
            x[i] = x_new[i];

        if (max_val > 0.0 && max_diff / max_val < Tol_range)
            return k;
    }

    printf("反復回数上限に到達\n");
    return MAX_ITER;
}

int main(void) {

    double A[N][N] = {0};
    double b[N]    = {0};
    double x[N]    = {0};

    ini_band_matrix(A, b, N);
    print_system(A, b, N);

    printf("***ヤコビ法を実行***\n\n");
    int iter = jacobi_iteration(A, b, x, N);
    print_solution(x, N, iter);

    return 0;
}


/* 出力関数 */
void print_system(const double (*A)[N], const double *b, int n) {
    printf("A =");
    for (int i = 0; i < 11; i++) printf("\t");
    printf("b =\n");

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%.1f ", A[i][j]);
        printf("\t%.1f\n", b[i]);
    }
    printf("\n");
}

void print_solution(const double *x, int n, int iter) {
    printf("反復回数: %d\n\n", iter);
    printf("近似解 x =\n");
    for (int i = 0; i < n; i++)
        printf("  x[%2d] = %s%.16f\n", i + 1, (x[i] >= 0) ? " " : "", x[i]);
    printf("\n");
}