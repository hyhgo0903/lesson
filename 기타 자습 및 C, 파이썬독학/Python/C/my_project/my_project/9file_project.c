#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX 10000
int main_file_project(void)
{
	// fgets fputs활용
	char line[MAX]; // 파일에서 불러온 내용을 저장
	char contents[MAX]; // 입력할 내용
	char password[20]; // 비밀번호 입력
	char c; // 비밀번호 입력할때 키값 확인용(******)

	printf("일기\n");
	printf("비밀번호 입력하세요(hyh) : ");

	// getchar()/ getch()의 차이
	// getchar() : 엔터를 입력받아야 동작
	// getch() : 키입력시 바로바로 동작

	int i = 0;
	while (1)
	{
		c = getch();
		if (c == 13) // enter입력시. 입력종료
		{
			password[i] = '\0'; // 문자열끝에 NULL문자
			// 문자열이 아니라
			// 문자변수 지정은 소문자로 해야되는것 주의
			break;
		}
		else // 비밀번호 입력 중
		{
			printf("*");
			password[i] = c;
		}
		i++;
	}
	//비밀번호 : "hyh"
	printf("\n\n=====비밀번호 확인 중=====\n\n");
	if (strcmp(password, "hyh") == 0)
	//스트링컴페어함수: 문자가 비교대상과 같은지
	//0이면 일치. 불일치시 문자열크기에따라 +1,-1출력
	{
		printf("\n=====비밀번호 확인 완료=====\n\n");
		char* fileName = "c:\\3DP\\diary.txt";
		FILE* file = fopen(fileName, "a+b");
		// a+b는 파일이 없으면 생성하고
		// 있으면 append 이어쓰기(뒤에 내용을 추가)
		if (file == NULL)
		{
			printf("\n=====파일 열기 실패=====\n\n");
			return 1;
		}

		while (fgets(line, MAX, file) != NULL)
		{
			printf("%s", line);
		}

		printf("\n\n 내용을 계속 작성하세요!\n");
		printf("종료하려면 EXIT입력\n");

		while (1)
		{
			scanf("%[^\n]", contents);
			// 줄바꿈(\n)이 나오기 전까지 모든 문자열을
			// 읽어들이라는 의미 (한 줄씩)
			getchar(); // Enter입력(\n)을 Flush처리(없앤다)

			if (strcmp(contents, "EXIT") == 0)
			{
				printf("입력을 종료합니다.\n\n");
				break;
			}
			fputs(contents, file);
			fputs("\n", file); // enter를 무시처리했으므로
		}
		fclose(file);
	}
	else
	{
		printf("비밀번호가 틀리고야 말았어.\n\n");
	}	

	return 0;
}