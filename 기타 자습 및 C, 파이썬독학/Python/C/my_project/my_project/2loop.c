#include <stdio.h>

int main_loop(void) // main을 중복해서 쓰면 오류
{
	int a = 10;
	a++;
	printf("a는 %d\n", a);
	int b = 20;
	printf("b :%d\n", ++b);
	// ++b : b = b + 1
	printf("b :%d\n", b++);
	// b++ : b를 수행하고 나서(연산할거 다하고 더함)
	// 다음문장으로 넘어갈때 b = b+1
	// b를 초항으로 쓰고싶을때 쓰면 됨
	printf("b : %d\n", b);

	// 반복문 for, while, do while
	//for (선언; 조건; 증감) {}
	for (int i = 1; i <= 5; i++)
	{
		printf("Hello %d\n", i);
	}
	//while (조건) {}
	int wi = 1;
	while (wi <= 5)
	{
		printf("Hell%d\n", wi++);
		// printf("Hell%d\n", wi);하고
		// wi++해도 결과는 같다
	}
	// do {} while (조건);
	int dwi = 1;
	do {
		printf("Helll%d\n", dwi++);
	} while (dwi <= 5);

	for (int ig = 1; ig <= 2; ig++)
	{
		printf("첫번째 반복문 : %d\n", ig);

		for (int jg = 1; jg <= 3; jg++)
		{
			printf("   두번째 반복문 : %d\n", jg);
		}
	}

	// 구구단 번잡하니 4단까지만
	for (int gu = 2; gu <= 4; gu++)
	{
		printf("%d단 :\n", gu);

		for (int gugu = 1; gugu <= 9; gugu++)
		{
			printf("   %d X %d : %d\n", gu, gugu, gu*gugu);
		}
	}
	for (int py = 0; py < 5; py++)
	{
		for (int ra = 0; ra <= py; ra++)
		{
			printf("*");
		}
		printf("\n");
	}

	for (int rpy = 0; rpy < 5; rpy++)
	{
		for (int rra = rpy; rra <= 5-1; rra++)
		{
			printf(" ");
		}
		for (int rrb = 0; rrb <= rpy; rrb++)
		{
			printf("*");
		}
		printf("\n");
	}

	int floor;
	printf("몇 층? : ");
	scanf_s("%d", &floor);
	for (int blo = 1; blo <= floor; blo++)
	{
		for (int spc = 1; spc <= (floor - blo); spc++)
		{
			printf(" ");
		}
		for (int doe = 1; doe <= (2 * blo) - 1; doe++)
		{
			printf("*");
		}
		printf("\n");
	}
	/* 이하는 모범답안
	for (int i = 0; i < floor; i++)
	{
		for (int j = i; j < (floor - 1); j++)
		{
			printf(" ");
		}
		for (int k = 0; k < (i * 2) + 1; k++)
		{
			printf("*");
		}
		printf("\n");
	*/
	return 0;
}