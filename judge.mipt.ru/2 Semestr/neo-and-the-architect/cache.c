#include <stdio.h>
#include <stdlib.h>

int GCD(int a, int b)
{

	if (a == 0)
		return b;
	if (b == 0)
		return a;
	int buffer;
	while (b != 0) {
		buffer = a % b;
		a = b;
		b = buffer;
	}
	return a;
}

void print_matrix(int *matrix, size_t N)
{
	size_t i, j;
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++)
			printf("%3d ", matrix[i * N + j]);
		printf("\n");
	}
	printf("\n\n");
}

void transpose_matrix(int *matrix, size_t N)
{
	size_t i, j;
	int buffer;
	for (i = 0; i < N; i++)
		for (j = i; j < N; j++) {
			buffer = matrix[i * N + j];
			matrix[i * N + j] = matrix[i + j * N];
			matrix[i + j * N] = buffer;
		}
}

void multiply_matrix(int *AB, int *A, int *B, size_t Ax, size_t Ay, size_t Bx,
		     size_t By)
{
	unsigned *AB_cell = AB;
	size_t ABy, ABx, i;
	for (ABy = 0; ABy < By; ABy++) {
		for (ABx = 0; ABx < Ax; ABx++) {
			int *A_row = &A[ABy * Ax];
			int *B_column = &B[ABx * By];
			*AB_cell = 0;
			for (i = 0; i < Ay; ++i)
				*AB_cell += *A_row++ ** B_column++;
			++AB_cell;
		}
	}
}

int main(int argc, char *argv[])
{
	size_t N, i, j;
	int divisor;
	int *A, *B, *AB;
	scanf("%zu %u", &N, &divisor);

	A = malloc(N * N * sizeof(int));
	B = malloc(N * N * sizeof(int));
	AB = malloc(N * N * sizeof(int));
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++) {
			A[N * i + j] = GCD(i + 1, j + 1);
			B[N * i + j] = GCD(N - i + 1, N - j + 1);
		}
	transpose_matrix(B, N);
	multiply_matrix(AB, A, B, N, N, N, N);

	size_t result = 0;
	for (i = 0; i < N * N; ++i)
		if (!(AB[i] % divisor))
			++result;

	printf("%zu\n", result);

	return 0;
}
