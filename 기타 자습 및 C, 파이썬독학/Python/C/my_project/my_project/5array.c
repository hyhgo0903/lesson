#include <stdio.h>

int main_array(void)
{
	int sub_array[3];
	/* 여러개의 변수를 동시에 생성
	 대괄호안은 요소 개수
	 3개니까 [0],[1],[2]에 저장 */
	sub_array[0] = 30;
	// 역시 index가 0부터 시작함
	// int 선언은 위에있으니까 하지X
	sub_array[1] = 40;
	sub_array[2] = 50;

	for (int i = 0; i < 3; i++)
	{
		printf("%d호칸에 %d명이 타고 있어\n", i + 1, sub_array[i]);
	}

	int arr[5] = { 1,3,5,7,9 };
	for (int i = 0; i < 5; i++)
	{
		printf("%d\n", arr[i]);
	}
	/* 선언만 해두면 (int arr[10];처럼)
	출력시에 더미값 나옴
	따라서 값은 반드시 초기화를 해야함

	다만, int arr[10] = {1,2}; 처럼
	하나라도 선언을 해두면
	다음 값부터는 자동으로 0을 넣어줌
	(하나도 선언 안해야 쓰레기값이 들어가는것)
	*/
	
	/*
	int size = 10;
	int arr[size];
	이렇게는 불가. 배열크기는 항상 상수만 넣어야
	*/
	int arr2[] = { 1,3,5,7,9,11,13,15,17,19 };
	// 이렇게 선언도 가능. 갯수를 세서 만들어줌
	float arr_f[5] = { 1.2f, 2.4f, 3.5f };
	for (int i = 0; i < 5; i++)
	{
		printf("%.2f\n", arr_f[i]);
	}
	// 문자 vs 문자열
	char c = 'A';
	printf("%c\n", c);

	char str[7] = "coding";
	printf("%s\n", str);
	/* 문자열끝엔 끝을 의미하는 NULL문자('\0;')가 포함되어야함
	(만약 6이 들어갔으면 coding뒤에 이상한 문자가 출력
		6개의 공간에 [c][o][d][i][n][g]들어가고
	한자리 남는 공간에[\0]이 자동으로 들어감.
	*/

	char str2[] = "1234567";
	printf("%s\n", str2);
	printf("%d\n", sizeof(str2));
	/* 공간없이 선언하면 자동으로 사이즈를
	글자를 읽고 NULL문자까지해서 char str2[8]로 생성해줌*/

	for (int i = 0; i < sizeof(str2); i++)
	{
		printf("%c\n", str2[i]);
	} // 출력해보면 마지막 한칸 비워있는데 NULL문자 자리
	char kor[] = "하융호";
	printf("%s\n", kor);
	printf("%d\n", sizeof(kor));
	/* 영어 한글자 : 1byte (= char 크기)
	한글은 2byte가 필요.
	따라서 2*3 + 1(NULL)인 7사이즈*/
	
	char str3[7] = { 'c','o','d','i','n','g','\0' };
	printf("%s\n", str3);

	char str4[10] = { 'c','o','d','i','n','g'};
	printf("%s\n", str4);
	for (int i = 0; i < sizeof(str4); i++)
	{
		printf("%c\n", str4[i]);
	}
	// 남는공간이 있으면 문자열끝이 자동으로 변한다.
	// sizeof(st4)는 10이므로 NULL포함된 공란 출력
	for (int i = 0; i < sizeof(str4); i++)
	{
		printf("%d\n", str4[i]);
		// 문자열(char)를 정수형 %d출력시
		// ASCII코드값 출력 NULL문자는 0으로 출력
	}

	char str5[256]; // 1prinfscanf에서 했던거
	printf("문자열을 입력하세요 : ");
	scanf_s("%s", str5, sizeof(str5));
	printf("%s\n", str5);

	/*
	ASCII코드 : ANSI(미국표준협회)에서 제시한 표준코드체계
	7bit : 총 128개 코드 [0-127]
	a:97, A:65, 0:48 */

	/*for (int i = 0; i < 128; i++)
	{
		printf("아스키코드 : %d = %c\n", i, i);
	}*/
	printf("%c\n", 'a');
	printf("%d\n", 'a');
	printf("%c\n", '\0');
	printf("%d\n", '\0');

	return 0;
}