#include <stdio.h>
#include <time.h>

int array_Animal[4][5];
int checkAnimal[4][5]; // ���������� ���� Ȯ��
char* strAnimal[10];
// ������������ �������
// char* sPtr = "�����̸�";
// ��� �Ѵٸ� "�����̸�"�� �޸� ������ ���������
// sPtr�� �� �ּҸ� ���Ե�. �̰ɷ� ���� ���ٰ���

void initAnimalArray();
void initAnimalName();
void shuffleAnimal();
void printAnimals();
void printQustion();
int getEmptyPosition();
int conv_pos_x(int x);
int conv_pos_y(int y);
int foundAllAnimal();

int main_multiarray_project(void)
{
	srand(time(NULL));
	initAnimalArray();
	initAnimalName();

	shuffleAnimal();

	int failCount = 0; // ����Ƚ��

	while (1)
	{
		int select1 = 0; // ����ڰ� ������ ó����
		int select2 = 0; // ����ڰ� ������ �ι�°��

		printAnimals(); // ������ġ���
		printQustion(); // ���� ��� (ī������)
		printf("������ ī�带 2�� ������ : ");
		scanf_s("%d %d", &select1, &select2);
		if (select1 == select2)
		{
			printf("������ �� �� ����\n\n");
			continue;
		}

		// ��ǥ�� �ش��ϴ� ī�带 ������ ������ Ȯ��
		int firSelect_x = conv_pos_x(select1);
		int firSelect_y = conv_pos_y(select1);

		int secSelect_x = conv_pos_x(select2);
		int secSelect_y = conv_pos_y(select2);

		if (checkAnimal[firSelect_x][firSelect_y]==0
			&& checkAnimal[secSelect_x][secSelect_y] == 0
			// ī�尡 �������� �ʾҴ��� ����
			&& array_Animal[firSelect_x][firSelect_y]
			== array_Animal[secSelect_x][secSelect_y])
			//�� ������ ������
		
		{
			printf("\n����! : %s �߰�\n\n",
				strAnimal[array_Animal[firSelect_x][firSelect_y]]);
			checkAnimal[firSelect_x][firSelect_y] = 1;
			checkAnimal[secSelect_x][secSelect_y] = 1;
		}
		else // �ٸ� ������ ���
		{
			printf("\nƲ�Ȱų� �̹� ������ ī��!\n\n");
			printf("%d : %s\n", select1,
				strAnimal[array_Animal[firSelect_x][firSelect_y]]);
			printf("%d : %s\n\n\n", select2,
				strAnimal[array_Animal[secSelect_x][secSelect_y]]);
			failCount++;
		}
		if (foundAllAnimal() == 1)
		{
			printf("\n\n��� ã����!\n\n");
			printf("\n\n������ Ƚ�� %d\n\n",failCount);
			break;
		}

	}

	return 0;
}

void initAnimalArray()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			array_Animal[i][j] = -1;
		}
	}
}

void initAnimalName()
{
	strAnimal[0] = "����";
	strAnimal[1] = "ȣ����";
	strAnimal[2] = "�䳢";
	strAnimal[3] = "������";
	strAnimal[4] = "�ϸ�";
	strAnimal[5] = "�����";
	strAnimal[6] = "������";
	strAnimal[7] = "����";
	strAnimal[8] = "�ڳ���";
	strAnimal[9] = "��Ÿ";
}

void shuffleAnimal()
{ // 20���� ī�忡 �̸��� ��� ��ġ
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			int pos = getEmptyPosition();
			int x = conv_pos_x(pos);
			int y = conv_pos_y(pos);

			array_Animal[x][y] = i;
		}
	}
}
int getEmptyPosition()
{ // ����� ã��
	while (1)
	{
		int randPos = rand() % 20; // 0~19
		// 1->[0,0] 19 -> [3,4]
		int x = conv_pos_x(randPos);
		int y = conv_pos_y(randPos);

		if (array_Animal[x][y] == -1) // �������
		{
			return randPos;
		}
	}
	return 0; // �̰� �ǹ̾���
}

int conv_pos_x(int x)
{// 19 -> [3,4]
	return x / 5;
} // �������̶� �˾Ƽ� ������
// 19 -> 3.8(������) -> 3
// 11 -> 2.2(������) -> 2

int conv_pos_y(int y)
{
	return y % 5;
} // ������Ȱ��. 19 -> 4, 11->1

void printAnimals()
{
	printf("\n====���α׷��ֻ����======\n");
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			printf("%8s", strAnimal[array_Animal[i][j]]);
			// 8ĭ���� Ȯ��
		}
		printf("\n");
	}
	printf("======================\n");
}
/*
                   seq                checkAnimal
������    0  1  �ϸ�  3  4        0 0 1 0 0
������    5  6  7  8  9           0 0 0 0 0
������   10 11 12 �ϸ� 14         0 0 0 1 0
������   15 16 17 18 19           0 0 0 0 0
*/
void printQustion()
{
	printf("\n\n(����)\n\n");
	int seq = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			// ����� ���� �������� �����̸�
			if (checkAnimal[i][j] != 0)
			{
				printf("%8s", strAnimal[array_Animal[i][j]]);
			}
			else
				printf("%8d", seq);
			// ���� ������ ��������(�����������)
			// �޸� -> ��ġ�� ��Ÿ���� ����
			seq++;
		}
		printf("\n");
	}
}
int foundAllAnimal()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (checkAnimal[i][j] == 0)
			{
				return 0;
			}
		}
	}
	return 1;
}