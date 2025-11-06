#include <stdio.h>
#include <stdlib.h>

int** allocateMatrix(int rows, int cols) {
    int** matrix = (int**) malloc(rows * sizeof(int*));  // allocate for rows, not cols
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*) malloc(cols * sizeof(int));
    }
    return matrix;
}

void freeMatrix(int** matrix, int rows) {
    for (int i = 0; i < rows; i++)
        free(matrix[i]);
    free(matrix);
}

void inputMatrix(int** matrix, int rows, int cols) {
    printf("Enter elements for matrix (%d*%d):\n", rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("Element [%d][%d]: ", i, j);
            scanf("%d", &matrix[i][j]);
        }
    }
}

void displayMatrix(int** matrix, int rows, int cols, char* title) {
    printf("%s (%d*%d):\n", title, rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);  // added space for readability
        }
        printf("\n");
    }
}

void addMatrix(int** A, int** B, int** sum, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            sum[i][j] = A[i][j] + B[i][j];
        }
    }
}

void multiplyMatrix(int** A, int** B, int** Product, int rowsA, int colsA, int colsB) {
    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsB; j++) {
            Product[i][j] = 0;
            for (int k = 0; k < colsA; k++) {
                Product[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    int rowsA, colsA, rowsB, colsB;

    printf("Enter dimensions for matrix A (rows cols): ");
    scanf("%d%d", &rowsA, &colsA);  // corrected to read colsA

    printf("Enter dimensions for matrix B (rows cols): ");
    scanf("%d%d", &rowsB, &colsB);

    int canAdd = (rowsA == rowsB && colsA == colsB);
    int canMultiply = (colsA == rowsB);

    int** A = allocateMatrix(rowsA, colsA);
    int** B = allocateMatrix(rowsB, colsB);
    int** Sum = NULL;
    int** Product = NULL;

    inputMatrix(A, rowsA, colsA);
    inputMatrix(B, rowsB, colsB);

    if (canAdd) {
        Sum = allocateMatrix(rowsA, colsA);
        addMatrix(A, B, Sum, rowsA, colsA);
        displayMatrix(Sum, rowsA, colsA, "Sum of A and B");
    } else {
        printf("Matrix addition not possible due to dimension mismatch\n");
    }

    if (canMultiply) {
        Product = allocateMatrix(rowsA, colsB);
        multiplyMatrix(A, B, Product, rowsA, colsA, colsB);  // fixed argument colsA passed correctly
        displayMatrix(Product, rowsA, colsB, "Product of A and B");
    } else {
        printf("Matrix multiplication is not possible due to dimension mismatch\n");
    }

    freeMatrix(A, rowsA);
    freeMatrix(B, rowsB);
    if (Sum) freeMatrix(Sum, rowsA);
    if (Product) freeMatrix(Product, rowsA);

    return 0;
}