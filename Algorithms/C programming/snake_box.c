/*
한 개의 정수 n과 자연수 k를 입력 받아 입력 받은 정수 n의 약수를 출력하고 그 중 k번 째로
작은 수를 출력하는 프로그램을 작성하시요. (1 < n < 5001)
*/

#include <stdio.h>
#include <string.h>

int main(void) {

	int n;
	printf("입력: ");
	scanf_s("%d", &n); // n*n의 달팽이 배열 크기를 입력 받음

	char arr[100][100]; // 100 이하의 n*n 배열이므로 2차원 배열 선언

	for(int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			arr[i][j] = ' '; // n*n의 배열을 공백으로 초기화한다
		}
	}

	int i = 0, j = 0;
	char num = '0';

	int isFinish = 0;
	int direction = 0;

	while (!isFinish) {

		switch (direction) {

		case 0: // 오른쪽 방향
			arr[i][j] = num++; // 달팽이 배열을 1씩 증가하며 채움
			if (arr[i][j + 1] != ' ') { // 오른쪽이 비어있지 않은 경우
				direction = 1; // 방향을 아래롤 이동
				++i; // 행의 값을 한칸 아래로 이동
			}
			else {
				++j; // 열의 값을 1 증가하여 이동
			}
			break;

		case 1: // 아래 방향
			arr[i][j] = num++;
			if (arr[i + 1][j] != ' '){ // 아래가 비어있지 않은 경우
				direction = 2; // 방향을 왼쪽으로 변경
				--j; // 행의 값을 한칸 왼쪽으로 이동
			}
			else {
				++i; // 행의 값을 1 증가하여 아래로 이동
			}
			break;

		case 2: // 왼쪽 방향
			arr[i][j] = num++;
			if (j == 0 || arr[i][j - 1] != ' ') { // 왼쪽이 비어있지 않은 경우
				direction = 3; //  방향을 위로 변경
				--i; // 행의 값을 1 위로 이동
			}
			else {
				--j; // 열의 값을 1 감소하여 왼쪽 이동
			}
			break;

		case 3: // 위로 방향
			arr[i][j] = num++;
			if (arr[i-1][j] != ' ') { // 위 값이 비어 있지 않은 경우
				direction = 0; // 방향을 오른쪽으로 변경
				//++i;
				++j; // 열의 값을 1 오른쪽 이동
			}
			else {
				--i; // 행의 값을 1 감소하여 위로 이동
			}
			break;
		}

		if (num > '9') {
			num = '0';
		}

		if (arr[i][j] != ' ') { // 달팽이 배열을 다 채운 경우 (현재 위치가 공백이 아닌 경우)
			isFinish = 1; // while문 탈출
		}
	}

	printf("\n[달팽이 사각형 출력]\n");
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			printf("%c ", arr[i][j]);
		}
		printf("\n");
	}
	return 0;
}