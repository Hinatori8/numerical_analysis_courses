#include <stdio.h>
#include <math.h>

#define N 3
void print_matrix(const char *name, const double (*M)[N], int n);


/*コレスキー分解関数*/
void cholesky_decomposition(const double (*A)[N], double (*L)[N], int n) {
    for (int j = 0; j < n; j++) {
        for (int i = j; i < n; i++) {
            double sum = 0.0;
            for (int k = 0; k < j; k++)
                sum += L[i][k] * L[j][k];

            if (i == j) L[i][i] = sqrt(A[i][i] - sum);
            else L[i][j] = (A[i][j] - sum) / L[j][j];
        }
    }
}

int main(void) {
    double A[N][N] = {
        {1,  1,  1},
        {1,  5,  5},
        {1,  5, 14}
    };
    double L[N][N] = {0};

    print_matrix("A", A, N);

    cholesky_decomposition(A, L, N); // A = L * L^T

    print_matrix("L", L, N);

    return 0;
}


/* 出力関数 */
void print_matrix(const char *name, const double (*M)[N], int n){
    printf("%s =\n", name);
    for (int i = 0; i < n; i++) {
        printf("  ");
        for (int j = 0; j < n; j++)
            printf("%6.1f ", M[i][j]);
        printf("\n");
    }
    printf("\n");
}