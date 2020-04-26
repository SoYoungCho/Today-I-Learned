/*
총 5줄의 입력이 주어졌을 때, 각 줄에는 최소 1개, 최대 15개의 글자들이 빈칸없이 연속으
로 주어진다. 다음 결과 화면과 같이 입력을 받고 결과를 출력하시요. 주어지는 글자는 영어
대문자 ‘A’부터 ‘Z 영어 소문자 ‘a’부터 ‘z 숫자 ‘0’부터 중 하나이다.
*/

#include <stdio.h>
#include <string.h> // strlen() 사용 위함

#define MAX_SIZE 16 // 문자열 뒤에 NULL문자가 들어갈 것 고려

int main() {
	char str[5][MAX_SIZE] = { 0, }; // 2차원 배열 선언 및 초기화
	int max = 0; // 문장 중 가장 긴 문장의 길이를 저장할 변수

	printf("5줄 입력: \n");
	for (int i = 0; i < 5; ++i) { // 5줄 입력 받는 반복문
		gets_s(str[i], sizeof(str[i])); // 문자열 입력 함수
		if ((int)strlen(str[i]) > max) { // 가장 긴 줄의 길이를 max에 저장
			max = strlen(str[i]);
		}
	}
	
	printf("\n[세로 읽기 출력]\n");
	for (int j = 0; j < max; ++j) { // 가장 긴 줄 max 만큼만 돌아 불필요한 반복 방지
		for (int i = 0; i < 5; ++i) {
			if (str[i][j] == 0 || str[i][j] == -2) { // 문자열 뒤 NULL 문자 0 혹은 비어있는 -2 일 경우 패스
				continue;
			}
			else {
				printf("%c", str[i][j]);
			}
		}
	}
	printf("\n");
	return 0;
	
}