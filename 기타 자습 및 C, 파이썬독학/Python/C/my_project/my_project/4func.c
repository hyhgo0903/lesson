#include <stdio.h>

/* 선언 (메인함수 위쪽에서)
이 함수를 쓸거야 하는것.
반환형 함수이름(전달값 = 파라미터);
반환형 : int / double / float / char..
반환하지 않을때는 void (return 필요X) */
void p(int num);
void func_without_return();
int func_with_return();
void func_with_params(int a, int b, int c);
int minus(int a, int b);

int main_func(void) // 이건 전달값없는 int형을 반환한단 뜻임
{
	int num = 5;
	p(num);
	num = num - 1; // 4
	p(num);
	num -= 1; // 3
	p(num);
	num *= 3; // 9
	p(num);
	num /= 3; // 3
	p(num);
	func_without_return();
	int ret = func_with_return();
	p(ret);
	func_with_params(1, 2, 3);
	ret = minus(5, 2);
	p(ret);
	printf("%d - %d = %d\n", 10, 4, minus(10, 4));

	return 0;
}

// 정의 (메인함수 아래)
void p(int num) // 이건 똑같이하되, ;은 x
{
	printf("입력값은 = %d\n", num);
}

void func_without_return()
{
	printf("반환값과 전달값이 없는 함수입니다.\n");
}
int func_with_return()
{
	printf("반환값이 있는 함수입니다.\n");
	return 10;
}
void func_with_params(int a, int b, int c)
{
	printf("전달값이 있는 함수입니다.\n전달값은 %d, %d, %d\n",
		a, b, c);
}
int minus(int a, int b)
{
	printf("반환값과 전달값이 있는 함수입니다.\n");
	return a - b;
}