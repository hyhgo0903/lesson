#include <stdio.h>
#include <time.h>

int lv; // �������� ����
int arrayFish[6];
int* cursor;

void initData();
void printFishes();
void decreaseWater(long a);
int checkFishAlive();

int main_pointer_project(void)
{
	long startTime = 0;
	// long�� �ð� ����. ���۽ð�
	long totalElapsedTime = 0;	// �� ��� �ð�
	long prevElapsedTime = 0;
	// ���� ��� �ð�(�ֱ� �� �� �ð�����)

	int num; // ������׿� ���� �ٰ����� �Է¹���.
	initData();

	cursor = arrayFish;

	startTime = clock();
	// ���� �ð��� millisecond(1/1000��)������ ��ȯ
	while (1)
	{
		printFishes();
		printf("�� �� ���׿� ��? ");
		scanf_s("%d", &num);

		// �Է°� üũ
		if (num < 1 || num > 6)
		{
			printf("�Է°��� �߸��Ǿ����ϴ�.");
			continue;
		}

		totalElapsedTime = (clock() - startTime) / CLOCKS_PER_SEC;
		// clock����(�и�������)�� �ʴ����� �ٲٱ� ���ؼ�
		printf("\n\n�� ����ð� : %ld ��\n", totalElapsedTime);

		//���� �� �� �ð�(���������� ���ؽð�) ���� �帥 �ð�
		prevElapsedTime = totalElapsedTime - prevElapsedTime;
		printf("�ֱ� ����ð� : %ld ��\n", prevElapsedTime);

		// ������ �� ����
		decreaseWater(prevElapsedTime);

		// �Է��� ���׿� ���� ��
		if (cursor[num - 1] <= 0)
		{
			printf("%d�� ������ �̹� ��� ���ֱ� ���\n", num);
		}
		else if(cursor[num - 1] +1 <= 100)
		{
			printf("%d���� ���ֱ�\n", num);
			cursor[num - 1] += 1;
		}

		// ������ �ø����� Ȯ��(20�ʸ���)
		if (totalElapsedTime / 20 > lv - 1)
		{
			lv++;
			printf("\n\n####������ %d��%d####\n\n", lv - 1, lv);
			if (lv == 5)
			{
				printf("####�ְ��� �޼�! ���� ����\n");
				exit(0);
			}
		}

		//��� ����Ⱑ �׾����� Ȯ��
		if (checkFishAlive() == 0)
		{
			printf("\n\n####��� ����Ⱑ �׾���####\n\n");
			exit(0);
		}
		else
		{
			printf("\n�Ѹ��� �̻� ���� ��� ����\n\n");
		}
		prevElapsedTime = totalElapsedTime;
	}

	return 0;
}

void initData()
{
	lv = 1; // ���� ���� (1~5)
	for (int i = 0; i < 6; i++)
	{
		arrayFish[i] = 100; // ������ ������ (0~100)
	}
}
void printFishes()
{
	printf("%3d�� %3d�� %3d�� %3d�� %3d�� %3d��\n", 1, 2, 3, 4, 5, 6);
	for (int i = 0; i < 6; i++)
	{
		printf(" %4d ", arrayFish[i]);
	}
	printf("\n\n");
}
void decreaseWater(long a)
{
	for (int i = 0; i < 6; i++)
	{
		arrayFish[i] -= (lv * 2 * (int)a); // 2�� ���̵� ���� ����
		if (arrayFish[i] < 0)
		{
			arrayFish[i] = 0;
		}
	}
}
int checkFishAlive()
{
	for (int i = 0; i < 6; i++)
	{
		if (arrayFish[i] > 0)
			return 1;	

	}
	return 0;
}