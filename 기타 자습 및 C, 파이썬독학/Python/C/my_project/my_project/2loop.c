#include <stdio.h>

int main_loop(void) // main�� �ߺ��ؼ� ���� ����
{
	int a = 10;
	a++;
	printf("a�� %d\n", a);
	int b = 20;
	printf("b :%d\n", ++b);
	// ++b : b = b + 1
	printf("b :%d\n", b++);
	// b++ : b�� �����ϰ� ����(�����Ұ� ���ϰ� ����)
	// ������������ �Ѿ�� b = b+1
	// b�� �������� ��������� ���� ��
	printf("b : %d\n", b);

	// �ݺ��� for, while, do while
	//for (����; ����; ����) {}
	for (int i = 1; i <= 5; i++)
	{
		printf("Hello %d\n", i);
	}
	//while (����) {}
	int wi = 1;
	while (wi <= 5)
	{
		printf("Hell%d\n", wi++);
		// printf("Hell%d\n", wi);�ϰ�
		// wi++�ص� ����� ����
	}
	// do {} while (����);
	int dwi = 1;
	do {
		printf("Helll%d\n", dwi++);
	} while (dwi <= 5);

	for (int ig = 1; ig <= 2; ig++)
	{
		printf("ù��° �ݺ��� : %d\n", ig);

		for (int jg = 1; jg <= 3; jg++)
		{
			printf("   �ι�° �ݺ��� : %d\n", jg);
		}
	}

	// ������ �����ϴ� 4�ܱ�����
	for (int gu = 2; gu <= 4; gu++)
	{
		printf("%d�� :\n", gu);

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
	printf("�� ��? : ");
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
	/* ���ϴ� ������
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