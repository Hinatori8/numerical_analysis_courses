#include <stdio.h>
#include <math.h>

#define N 5
void print_vector(const char *name, const double *v, int n);
void print_matrix(const char *name, const double (*A)[N], int rows, int cols);
void print_solution(const double *x, int n);

/*ガウスの消去法の実行関数群*/
void forward_elimination(double (*A)[N], double *b, int n) {
    for (int k = 0; k < n - 1; k++) {
        for (int i = k + 1; i < n; i++) {
            double m = A[i][k] / A[k][k];
            for (int j = k; j < n; j++)
                A[i][j] -= m * A[k][j];
            b[i] -= m * b[k];
        }
    }
}

void back_substitution(const double (*A)[N], const double *b, double *x, int n) {
    x[n - 1] = b[n - 1] / A[n - 1][n - 1];
    for (int i = n - 2; i >= 0; i--) {
        x[i] = b[i];
        for (int j = i + 1; j < n; j++)
            x[i] -= A[i][j] * x[j];
        x[i] /= A[i][i];
    }
}


int main(void) {
    double A[N][N] = {
        {1, 2, 1, 2, 1},
        {2, 3, 2, 3, 2},
        {1, 2, 3, 4, 5},
        {4, 3, 8, 1, 2},
        {8, 2, 4, 1, 9}
    };
    double b[N] = {1, 2, 3, 4, 5};
    double x[N] = {0};

    print_matrix("A", A, N, N);
    print_vector("b", b, N);

    printf("***ガウスの消去法を実行***\n\n");
    forward_elimination(A, b, N);  // 前進消去
    back_substitution(A, b, x, N); // 後退代入

    print_solution(x, N);

    return 0;
}

/* 出力関数 */
void print_vector(const char *name, const double *v, int n) {
    printf("%s =\n", name);
    for (int i = 0; i < n; i++)
        printf("  %.1f\n", v[i]);
    printf("\n");
}

void print_matrix(const char *name, const double (*A)[N], int rows, int cols) {
    printf("%s =\n", name);
    for (int i = 0; i < rows; i++) {
        printf("  ");
        for (int j = 0; j < cols; j++)
            printf("%6.1f ", A[i][j]);
        printf("\n");
    }
    printf("\n");
}

void print_solution(const double *x, int n) {
    for (int i = 0; i < n; i++)
        printf("  x[%d] = %s%.16f\n", i + 1, (x[i] >= 0) ? " " : "", x[i]);
    printf("\n");
}
