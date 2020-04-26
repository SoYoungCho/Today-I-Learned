/*
한 개의 정수 n과 자연수 k를 입력 받아 입력 받은 정수 n의 약수를 출력하고 그 중 k번 째로
작은 수를 출력하는 프로그램을 작성하시요. (1 < n < 5001)
*/

#include <stdio.h>
#include <string.h> // strlen() 사용 위함
#include <math.h> // root 연산 sqrt 사용 위함

int main(void) {
	int n, k;
	int count = 0; // primeArr 배열에 순서대로 저장하기 위한 count 변수

	printf("입력: ");
	scanf_s("%d %d", &n, &k); // 약수를 구할 숫자 n, 몇 번째 약수 출력할지의 k
	int* primeArr = malloc((int)sqrt(n) * sizeof(int));

	int arr1[5000], arr2[5000], count1 = 0, count2 = 0; // 작은 약수와 큰 약수를 저장할 배열 2개, 약수의 개수를 카운팅할 변수
	int i;

	for (i = 1; i*i < n; ++i) { // n의 제곱근만큼 돌며 약수여부를 확인. < 대신 <= 일 경우 arr1, arr2에 모두 저장되므로 하단 조건문을 통해 예외적으로 적용
		if (n % i == 0) { // 약수는 나누었을 때 나머지가 0
			arr1[count1++] = i; // 작은 약수의 역할
			arr2[count2++] = n / i; // n 나누기 작은 약수 몫은 큰 약수 역할
		}
	}

	if (i * i == n) { // i가 arr1, arr2에 두 번 저장되지 않도록 하는 조건문
		arr1[count1++] = i;
	}

	printf("\n[약수 출력]\n");

	for (int i = 0; i < count1; ++i) { // arr1의 값은 왼쪽에서 오른쪽으로 출력
		printf("%d ", arr1[i]);
		primeArr[count++] = arr1[i]; // 약수를 배열 primeArr에 저장한다
	}

	for (int i = count2 - 1; i >= 0; --i) { // arr2의 값은 오른쪽에서 왼쪽으로 출력
		printf("%d ", arr2[i]);
		primeArr[count++] = arr2[i];  // 약수를 배열 primeArr에 저장한다
	}
	printf("\n\n[%d번째로 작은 수 출력]\n", k);
	printf("%d", primeArr[k-1]);

	free(primeArr); // 메모리 해제
	return 0;
}