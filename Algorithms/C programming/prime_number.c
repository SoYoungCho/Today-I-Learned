/*
�� ���� ���� n�� �ڿ��� k�� �Է� �޾� �Է� ���� ���� n�� ����� ����ϰ� �� �� k�� °��
���� ���� ����ϴ� ���α׷��� �ۼ��Ͻÿ�. (1 < n < 5001)
*/

#include <stdio.h>
#include <string.h> // strlen() ��� ����
#include <math.h> // root ���� sqrt ��� ����

int main(void) {
	int n, k;
	int count = 0; // primeArr �迭�� ������� �����ϱ� ���� count ����

	printf("�Է�: ");
	scanf_s("%d %d", &n, &k); // ����� ���� ���� n, �� ��° ��� ��������� k
	int* primeArr = malloc((int)sqrt(n) * sizeof(int));

	int arr1[5000], arr2[5000], count1 = 0, count2 = 0; // ���� ����� ū ����� ������ �迭 2��, ����� ������ ī������ ����
	int i;

	for (i = 1; i*i < n; ++i) { // n�� �����ٸ�ŭ ���� ������θ� Ȯ��. < ��� <= �� ��� arr1, arr2�� ��� ����ǹǷ� �ϴ� ���ǹ��� ���� ���������� ����
		if (n % i == 0) { // ����� �������� �� �������� 0
			arr1[count1++] = i; // ���� ����� ����
			arr2[count2++] = n / i; // n ������ ���� ��� ���� ū ��� ����
		}
	}

	if (i * i == n) { // i�� arr1, arr2�� �� �� ������� �ʵ��� �ϴ� ���ǹ�
		arr1[count1++] = i;
	}

	printf("\n[��� ���]\n");

	for (int i = 0; i < count1; ++i) { // arr1�� ���� ���ʿ��� ���������� ���
		printf("%d ", arr1[i]);
		primeArr[count++] = arr1[i]; // ����� �迭 primeArr�� �����Ѵ�
	}

	for (int i = count2 - 1; i >= 0; --i) { // arr2�� ���� �����ʿ��� �������� ���
		printf("%d ", arr2[i]);
		primeArr[count++] = arr2[i];  // ����� �迭 primeArr�� �����Ѵ�
	}
	printf("\n\n[%d��°�� ���� �� ���]\n", k);
	printf("%d", primeArr[k-1]);

	free(primeArr); // �޸� ����
	return 0;
}