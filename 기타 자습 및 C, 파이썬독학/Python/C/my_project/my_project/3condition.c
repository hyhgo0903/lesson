#include <stdio.h>
#include <time.h>

int main_condition(void)
{
	int age = 10;
	if (age >= 20) // if (����) {}
	{
		printf("����\n");
	}
	else if (age >= 14 && age <= 16)
	{ // ���̽� and�� ���⼱ &&
		printf("���л�\n");
	}
	else if (age >= 17)
	{
		printf("����л�\n");
	}
	else // else {}
	{
		printf("�ʵ�����\n");
	}
	// ���ǿ� ������ if ������ Ż��
	// ���� else if�� else�� ã��X
	for (int stu = 1; stu <= 30; stu++)
	{
		if (stu > 5)
		{
			printf("�������\n");
			break; // for�� Ż��
		}
		printf("%d �� �⼮\n", stu);
	}

	for (int stu = 1; stu <= 30; stu++)
	{
		if (stu >= 10 && stu <= 15)
		{
			if (stu == 14)
			{
				printf("%d �� �л��� �Ἦ\n", stu);
				continue; // for�� ������ȣ��
			}
			printf("%d �� �⼮2\n", stu);			
		}
	}
	int al = 12;
	if (al <= 15 && al >= 10)
	{ // &&�� and
		printf("al�� 10�̻� 15����\n");
	}
	else
	{
		printf("al�� 10�̸��̰ų� 15�ʰ�\n");
	}
	if (al > 15 || al < 10)
	{ // ||�� or
		printf("al�� 10�̸��̰ų� 15�ʰ�\n");
	}
	else
	{
		printf("al�� 10�̻� 15����\n");
	}
	srand(time(NULL)); // 3+random.c����
	int num1 = rand() % 3;
	if (num1 == 0)
	{
		printf("����\n");
	}
	else if (num1 == 1)
	{
		printf("����\n");
	}
	else
	{
		printf("��\n");
	}

	int num2 = rand() % 3;
	switch (num2) // ���� �޴´�
	{
	case 0:printf("����\n"); break;
	// break ������ ���ϱ����� ���� �Ⱥ��� ����
	case 1:printf("����\n"); break;
	case 2:printf("��\n"); break;
	default:printf("??\n");
	}
	
	age = 10;
	switch (age) // ���� �޴´�
	{
	case 8:
	case 9:
	case 10:
	case 11:
	case 12:
	case 13: printf("�ʵ��л��Դϴ�.\n"); break;
	case 14:
	case 15:
	case 16: printf("���л��Դϴ�.\n"); break;
	case 17:
	case 18:
	case 19: printf("����л��Դϴ�.\n"); break;
	default:  printf("�л� �ƴ�\n"); break;
	}

	srand(time(NULL));
	int ud = rand() % 100 + 1;
	printf("����: %d\n", ud);
	int answer = 0;
	int chance = 5;
	while (chance > 0) // ���� ���ַ��� ��ȣ�ȿ�
		// 1(��)�� ������ �� while (1) (���ѷ���)
	{
		printf("���� ��ȸ: %d\n", chance--);
		printf("�����Է�(1~100): \n");
		scanf_s("%d", &answer);

		if (answer > ud)
		{
			printf("DOWN\n\n");
		}
		else if (answer < ud)
		{
			printf("UP\n\n");
		}
		else if(answer == ud)
		{
			printf("Correct");
			break;
		}
		else
		{
			printf("�����߻�");
			break;
		}
		if (chance == 0)
		{
			printf("Fail");
			break;
		}
	}
	return 0;
}