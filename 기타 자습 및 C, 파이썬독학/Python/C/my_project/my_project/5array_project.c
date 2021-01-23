#include <stdio.h>
#include <time.h>

int main_array_project(void)
{
	srand(time(NULL));
	printf("\n\n === �߸��� === \n\n");
	int answer;
	int treatment = rand() % 4; // �߸�������(0~3)

	int cntShowBottle = 0; // ������ �� ����
	int prevCntShowBottle = 0;// �հ��ӿ� ������ �� ����
	// ���� �����ִ� ������ �޶� �������

	for (int i = 1; i <= 3; i++)
	{
		int bottle[4] = { 0,0,0,0 }; // �� 4��
		do {
			cntShowBottle = rand() % 2 + 2; // 2~3
		} while (cntShowBottle == prevCntShowBottle);
		// ������ �ٸ��� ���������� while���� �� ���
		prevCntShowBottle = cntShowBottle;
		// �ΰ�������µ� �� �ΰ��������� �ʵ���

		int isincluded = 0; // �߸������Կ���
		printf("%d��° �õ� : ", i);

		//������ �� ���� ����
		for (int j = 0; j < cntShowBottle; j++)
		{
			int randBottle = rand() % 4; // 0~3

			// ���� ���õ��� ���� ���̸� ����ó��
			if (bottle[randBottle] == 0)
			{
				bottle[randBottle] = 1;
				if (randBottle == treatment)
				{
					isincluded = 1;
				}
			}
			// ���õ� ���̸� �ٽ� ����
			else
			{
				j--;
			}
		}
		// ����ڿ��� ���� ǥ��
		for (int k = 0; k < 4; k++)
		{
			if (bottle[k] == 1)
				printf("%d ", k + 1);
		}
		printf("������ �Ӹ��� �ٸ��ϴ�.\n\n");
		if (isincluded == 1)
		{
			printf("�Ӹ��� �ڶ�\n");
		}
		else
		{
			printf("�Ӹ��� �ڶ��� ����\n");
		}

		printf("\n>> ����Ϸ��� �ƹ�Ű�� ��������\n");
		getchar(); // ����ڿ��� Ű�� �Է¹���������
		// ����ϴ� �Լ�
	}

	printf("\n�߸����� ����ϱ��?\n");
	scanf_s("%d", &answer);

	if (answer == treatment + 1)
	{
		printf("\n����!\n");
	}
	else
	{
		printf("\n����! ������ %d\n", treatment + 1);
	}
	return 0;
}