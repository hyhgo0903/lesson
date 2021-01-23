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
			printf("����\n");
			exit(0);
			/* exit�� for�� Ż��� �ƴ϶�
			�׳� �ٷ� ���α׷��� ������� �ǹ���.*/
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
	printf("\n\n ����� 5���� %d���� �����", count);
	return 0;
}

int getRandomNumer(int lv)
{
	return rand() % (lv * 7) + 1;
}
void showQuestion(int lv, int a, int b)
{
	printf("\n\n####%d ��° ����####\n\n", lv);
	printf("\n\t%d x %d ?\n\n", a, b);
	printf("################\n");
	printf("\n������ �Է��϶� (���� : -1)\n");
}
void success()
{
	printf("\n\n����\n\n");
}
void fail()
{
	printf("\n\nƲ��\n\n");
}