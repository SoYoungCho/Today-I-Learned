#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {

	// 1차원 배열에 1부터 9까지 순서대로 나열
	int array1D[9] = { 0, };
	for (int i = 0; i < 9; i++) {
		array1D[i] = (i + 1);
	}

	// 난수를 이용해서 배열의 값을 뒤섞기
	srand(time(NULL));
	for (int i = 0; i < 8; i++) {
		int rand_num = rand() % (9 - i) + i;
		int tmp = array1D[i];
		array1D[i] = array1D[rand_num];
		array1D[rand_num] = tmp;
	}

	// M 행렬
	int matrix_M[3][3] = { 0, };
	int t = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			matrix_M[i][j] = array1D[t];
			t++;
		}
	}

	// M행렬 출력
	printf("[ 3x3 행렬 M ]\n");
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			printf("%d", matrix_M[i][j]);
			if (j == 2) {
				printf("\n");
			}
		}
		if (i == 2) {
			printf("\n");
		}
	}


	// X1 행렬
	int matrix_X1[3][3] = {
		{0, 0, 1},
		{1, 0, 0},
		{0, 1, 0}
	};

	// X2 행렬
	int matrix_X2[3][3] = {
		{0, 1, 0},
		{0, 0, 1},
		{1, 0, 0}
	};

	// 9개의 스도쿠 행렬 M0 ~ M8을 위한 3차원 행렬
	int matrix[9][3][3] = { 0, };

	// M0 = M
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			matrix[0][i][j] = matrix_M[i][j];
		}
	}

	// M1 = X2 *M
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			int sum = 0;
			for (int k = 0; k < 3; k++) {
				sum += (matrix_X2[i][k] * matrix_M[k][j]);
			}
			matrix[1][i][j] = sum;
		}
	}

	// M2 = X1 * M
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			int sum = 0;
			for (int k = 0; k < 3; k++) {
				sum += (matrix_X1[i][k] * matrix_M[k][j]);
			}
			matrix[2][i][j] = sum;
		}
	}

	// M3 = M * X1
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			int sum = 0;
			for (int k = 0; k < 3; k++) {
				sum += (matrix_M[i][k] * matrix_X1[k][j]);
			}
			matrix[3][i][j] = sum;
		}
	}

	// M4 = X2 * M * X1
	int tmp[3][3] = { 0, };
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			int sum = 0;
			for (int k = 0; k < 3; k++) {
				sum += (matrix_X2[i][k] * matrix_M[k][j]);
			}
			tmp[i][j] = sum;
		}
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			int sum = 0;
			for (int k = 0; k < 3; k++) {
				sum += (tmp[i][k] * matrix_X1[k][j]);
			}
			matrix[4][i][j] = sum;
		}
	}

	// M5 = X1 * M * X1
	int tmp5[3][3] = { 0, };
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			int sum = 0;
			for (int k = 0; k < 3; k++) {
				sum += (matrix_X1[i][k] * matrix_M[k][j]);
			}
			tmp5[i][j] = sum;
		}
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			int sum = 0;
			for (int k = 0; k < 3; k++) {
				sum += (tmp5[i][k] * matrix_X1[k][j]);
			}
			matrix[5][i][j] = sum;
		}
	}

	// M6 = M * X2
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			int sum = 0;
			for (int k = 0; k < 3; k++) {
				sum += (matrix_M[i][k] * matrix_X2[k][j]);
			}
			matrix[6][i][j] = sum;
		}
	}

	// M7 = X2 * M * X2
	int tmp7[3][3] = { 0, };
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			int sum = 0;
			for (int k = 0; k < 3; k++) {
				sum += (matrix_X2[i][k] * matrix_M[k][j]);
			}
			tmp7[i][j] = sum;
		}
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			int sum = 0;
			for (int k = 0; k < 3; k++) {
				sum += (tmp7[i][k] * matrix_X2[k][j]);
			}
			matrix[7][i][j] = sum;
		}
	}

	// M8 = X1 * M * X2
	int tmp8[3][3] = { 0, };
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			int sum = 0;
			for (int k = 0; k < 3; k++) {
				sum += (matrix_X1[i][k] * matrix_M[k][j]);
			}
			tmp8[i][j] = sum;
		}
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			int sum = 0;
			for (int k = 0; k < 3; k++) {
				sum += (tmp8[i][k] * matrix_X2[k][j]);
			}
			matrix[8][i][j] = sum;
		}
	}

	// result_matrix
	int result_matrix[9][9] = { 0, };
	for (int k = 0; k < 9; k++) { // M0부터 M8까지 9개의 3X3 행렬
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				// M0 ~ M8까지의 9개의 3X3 행렬의 각 값들을 전체 9X9 행렬에 넣도록 인덱스를 변환
				result_matrix[3 * (k / 3) + i][3 * (k % 3) + j] = matrix[k][i][j];
			}
		}
	}

	printf("[ 스도쿠 생성 결과 ]\n");
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			printf("%d", result_matrix[i][j]);
			if (j % 3 == 2) { // 열 단위로 띄어쓰기
				printf(" ");
			}
		}
		if (i % 3 == 2) { // 3개의 행렬 출력 후 개행
			printf("\n");
		}
		printf("\n");
	}

	return 0;
}
