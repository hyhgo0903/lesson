#define _CRT_SECURE_NO_WARNINGS
// fopen쓸때 에러방지
// fopen_s를 써도 되긴한데 호환이 문제
#include <stdio.h>
#define MAX 10000 // 상수로

int main_file(void)
{
	/*파일 입출력 : 저장 불러오기
	fputs/ fgets 쌍 --> 문자열 저장, 불러오기
	fprintf/ fscanf 쌍 --> 정형화된 포맷으로 읽고쓸때
	printf, scanf 함수의 %d, %s, &num 등 형식을 생각*/

	char line[MAX]; // == char line[10000];
	FILE* file = fopen("c:\\3DP\\test1.txt", "wb");
	/* \ 하나만 적으면X (탈출문자 \n \t...)
	여는방식 : r(read) 읽기전용
	w(rite) 쓰기전용. 이미 있는파일이면 내용을 싹 지워버림
	a(ppend) 이어쓰기
	뒤에는 t(text) b(binary data)*/
	if (file == NULL)
	{
		printf("열기 실패\n");
		return 1; // 프로그램 종료
	}

	fputs("fputs를 이용해서 저장할 내용\n", file);
	fputs("잘 적혔는지 확인\n", file);

	fclose(file); // 파일을 저장하고 닫음
	// 파일을 연채 에러나면 데이터 손실 가능.
	// 파일은 항상 닫아주는 습관을 가지자

	FILE* file2 = fopen("c:\\3DP\\test1.txt", "rb");
	if (file2 == NULL)
	{
		printf("열기 실패\n");
		return 1;
	}
	while (fgets(line, MAX, file2) != NULL)
	// line에다가 저장하는것. 한줄씩
	// fgets(저장될곳, 사이즈, 파일)
	{
		printf("%s", line);
	}
	fclose(file2);

	int num[6] = { 0,0,0,0,0,0 }; // 추첨번호
	int bonus = 0; // 보너스번호
	char str1[MAX];
	char str2[MAX];
	FILE* file3 = fopen("c:\\3DP\\test2.txt", "wb");
	if (file3 == NULL)
	{
		printf("열기 실패\n");
		return 1;
	}
	
	fprintf(file3, "%s %d %d %d %d %d %d\n",
		"추첨번호:", 1, 2, 3, 4, 5, 6);
	fprintf(file3, "%s %d\n", "보너스번호:", 7);
	// fprintf(파일, 이후는 printf와 비슷)
	fclose(file3);

	FILE* file4 = fopen("c:\\3DP\\test2.txt", "rb");
	if (file4 == NULL)
	{
		printf("열기 실패\n");
		return 1;
	}

	fscanf(file4, "%s %d %d %d %d %d %d", str1, &num[0],
		&num[1], &num[2], &num[3], &num[4], &num[5]);
	// fscanf(파일, 내용, 저장할곳)
	printf("%s %d %d %d %d %d %d\n", str1, num[0],
		num[1], num[2], num[3], num[4], num[5]);

	fscanf(file4, "%s %d", str2, &bonus); // 두번째줄
	printf("%s %d\n", str2, bonus);

	return 0;
}