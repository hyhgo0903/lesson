#include <stdio.h>
// stdio = standard input/output library

int main_printf(void)
{
	int age = 12;
	printf("%d\n", age);
	// %d는 정수형값을 출력하라는 의미. age가 %d위치로
	// \n은 줄바꿈(end)
	age = 13; // 앞서 int라고 선언됐기 때문에 생략
	printf("%d\n", age);
	/*주석 :
	다음별슬러시까지
	모두 무시*/

	float f = 50.5f; // float 끝엔 꼭 f를 써줄것
	printf("%f\n", f);
	printf("%.2f\n", f);
	// .2는 소수점 둘째까지 출력하란 뜻
	double d = 4.428;
	printf("%.2lf\n", d);

	const int year = 1991; // 상수
	printf("생년: %d\n", year);
	// year = 2001; 라하면 오류

	int add = 3 + 7;
	printf("3 + 7 = %d\n", add);
	printf("%d X %d = %d\n", 3, 7, 3 * 7);

	// scanf = 키보드입력을 받아서 저장
	int input;
	printf("값을 입력하세요 : ");
	scanf_s("%d", &input);
	// input이란 변수에 입력받겠다는 뜻
	printf("입력값 : %d\n", input);

	int one, two, three;
	printf("3개의 정수를 입력하세요 : ");
	scanf_s("%d %d %d", &one, &two, &three);
	printf("1 : %d\n", one);
	printf("2 : %d\n", two);
	printf("3 : %d\n", three);

	char c = 'A';
	printf("%c\n", c);
	// 문자char(한글자) 작은따옴표
	char str[256];
	// 256개의 공간에 문자열(여러글자) 만든다
	printf("문자열을 입력하세요 : ");
	scanf_s("%s", str, sizeof(str));
	// 앤드표시없이 str
	// 더 큰 문자열을 입력받으면 곤란하므로
	// sizeof로 256개 공간을 쓰겠다 하는것.
	printf("%s\n", str);

	// 프로젝트 : 정보를 입수
	char name[256];
	printf("이름? ");
	scanf_s("%s", name, sizeof(name));

	int age2;
	printf("나이? ");
	scanf_s("%d", &age2);
	
	float weight;
	printf("몸무게? ");
	scanf_s("%f", &weight);

	double height;
	printf("키? ");
	scanf_s("%lf", &height);

	printf("\n\n --- 정보 ---\n\n");
	printf("이름 :   %s\n", name);
	printf("나이 :   %d\n", age2);
	printf("몸무게 : %.2f\n", weight);
	printf("키 :     %.2lf\n", height);
	return 0;
}