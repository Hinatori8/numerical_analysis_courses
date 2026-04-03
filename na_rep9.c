#include <stdio.h>
#include <math.h>

#define ROWS 5
#define COLS 3
void print_matrix_rc(const char *name, const double *M, int rows, int cols);
void print_matrix_sq(const char *name, const double *M, int n, int precision);
void print_vector(const char *name, const double *v, int n, int precision);

/* 行列の転置 */
void transpose(const double *A, double *A_T, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            A_T[j * rows + i] = A[i * cols + j];
}

/* 行列の積と行列ベクトル積 */
void mat_mul(const double *A, const double *B, double *C,int m, int inner, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            double sum = 0.0;
            for (int k = 0; k < inner; k++)
                sum += A[i * inner + k] * B[k * n + j];
            C[i * n + j] = sum;
        }
    }
}

void mat_vec_mul(const double *A, const double *v, double *result,int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        double sum = 0.0;
        for (int j = 0; j < cols; j++)
            sum += A[i * cols + j] * v[j];
        result[i] = sum;
    }
}

/* コレスキー分解関数 */
void cholesky_decomposition(const double *A, double *L, int n) {
    for (int j = 0; j < n; j++) {
        for (int i = j; i < n; i++) {
            double sum = 0.0;
            for (int k = 0; k < j; k++)
                sum += L[i * n + k] * L[j * n + k];

            if (i == j)
                L[i * n + i] = sqrt(A[i * n + i] - sum);
            else
                L[i * n + j] = (A[i * n + j] - sum) / L[j * n + j];
        }
    }
}

void forward_substitution(const double *L, const double *b, double *y, int n) {
    for (int i = 0; i < n; i++) {
        y[i] = b[i];
        for (int j = 0; j < i; j++)
            y[i] -= L[i * n + j] * y[j];
        y[i] /= L[i * n + i];
    }
}

void back_substitution(const double *L, const double *y, double *x, int n) {
    for (int i = n - 1; i >= 0; i--) {
        x[i] = y[i];
        for (int j = i + 1; j < n; j++)
            x[i] -= L[j * n + i] * x[j];
        x[i] /= L[i * n + i];
    }
}

int main(void) {
    double A[ROWS * COLS] = {
         0.5, -1.0,  1.5,
        -2.0, -2.5, -3.0,
         3.5, -4.0,  4.5,
        -5.0, -5.5, -6.0,
         6.5, -7.0,  7.5
    };
    double b[ROWS] = {1, 1, 1, 1, 1};

    double A_T[COLS * ROWS]  = {0};
    double ATA[COLS * COLS]  = {0};
    double ATb[COLS]         = {0};
    double L[COLS * COLS]    = {0};
    double y[COLS]           = {0};
    double x[COLS]           = {0};

    print_matrix_rc("A", A, ROWS, COLS);
    print_vector("b", b, ROWS, 1);

    transpose(A, A_T, ROWS, COLS);          // A^T
    mat_mul(A_T, A, ATA, COLS, ROWS, COLS);
    mat_vec_mul(A_T, b, ATb, COLS, ROWS);

    print_matrix_sq("A^T*A", ATA, COLS, 2);
    print_vector("A^T*b", ATb, COLS, 1);

    cholesky_decomposition(ATA, L, COLS);  // コレスキー分解
    print_matrix_sq("L", L, COLS, 16);

    forward_substitution(L, ATb, y, COLS); // 前進消去
    print_vector("y", y, COLS, 16);

    back_substitution(L, y, x, COLS);      // 後退代入
    print_vector("x", x, COLS, 16);

    return 0;
}


/* 出力関数 */
void print_matrix_rc(const char *name, const double *M, int rows, int cols) {
    printf("%s =\n", name);
    for (int i = 0; i < rows; i++) {
        printf("  ");
        for (int j = 0; j < cols; j++) {
            double v = M[i * cols + j];
            printf("%s%.1f ", (v >= 0) ? " " : "", v);
        }
        printf("\n");
    }
    printf("\n");
}

void print_matrix_sq(const char *name, const double *M, int n, int precision) {
    printf("%s =\n", name);
    for (int i = 0; i < n; i++) {
        printf("  ");
        for (int j = 0; j < n; j++) {
            double v = M[i * n + j];
            printf("%s%.*f ", (v >= 0) ? " " : "", precision, v);
        }
        printf("\n");
    }
    printf("\n");
}

void print_vector(const char *name, const double *v, int n, int precision) {
    printf("%s =\n", name);
    for (int i = 0; i < n; i++) {
        if (precision <= 1)
            printf("  %s%.1f\n", (v[i] >= 0) ? " " : "", v[i]);
        else
            printf("  %.16f\n", v[i]);
    }
    printf("\n");
}