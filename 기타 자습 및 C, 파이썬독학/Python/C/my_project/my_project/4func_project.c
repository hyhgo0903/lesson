#include <stdio.h>
#include <time.h>

int getRandomNumer(int lv);
void showQuestion(int lv, int a, int b);
void success();
void fail();

int main_func_project(void)
{
	srand(time(NULL));
	int count = 0;
	for (int i = 1; i <= 5; i++)
	{
		int num1 = getRandomNumer(i);
		int num2 = getRandomNumer(i);
		showQuestion(i, num1, num2);
		int answer = -1;
		scanf_s("%d", &answer);
		if (answer == -1)
		{
			printf("포기\n");
			exit(0);
			/* exit는 for문 탈출뿐 아니라
			그냥 바로 프로그램을 끝내라는 의미임.*/
		}
		else if (answer == num1 * num2)
		{
			success();
			count++;
		}
		else
		{
			fail();
		}

	}
	printf("\n\n 당신은 5번중 %d개를 맞췄다", count);
	return 0;
}

int getRandomNumer(int lv)
{
	return rand() % (lv * 7) + 1;
}
void showQuestion(int lv, int a, int b)
{
	printf("\n\n####%d 번째 문제####\n\n", lv);
	printf("\n\t%d x %d ?\n\n", a, b);
	printf("################\n");
	printf("\n정답을 입력하라 (종료 : -1)\n");
}
void success()
{
	printf("\n\n정답\n\n");
}
void fail()
{
	printf("\n\n틀림\n\n");
}