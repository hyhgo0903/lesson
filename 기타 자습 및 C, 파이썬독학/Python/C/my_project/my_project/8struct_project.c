#include <stdio.h>
#include <time.h>

typedef struct {
	char* name;
	int age;	
} CAT;

//������� ������ �����
int collect[5] = { 0,0,0,0,0 };

//��ü ����� ����Ʈ
CAT cats[5];

void initCats(); // ����� ���� �ʱ�ȭ
void printCat(int selected);
int checkCollection();

int main_struct_project(void)
{
	srand(time(NULL));

	initCats();

	while (1)
	{
		printf("��í����! �ƹ�Ű�� ������ Ȯ��\n");
		getchar();

		int selected = rand() % 5; // 0~4
		printCat(selected); // ����� ���� ���
		collect[selected] = 1; // ����� �̱� ó��
		
		int collectAll = checkCollection();
		if (collectAll == 1)
		{
			break;
		}
	}
	return 0;
}

void initCats()
{
	cats[0].name = "ůů��";
	cats[0].age = 5;
	cats[1].name = "����";
	cats[1].age = 3;
	cats[2].name = "�ɷ���";
	cats[2].age = 4;
	cats[3].name = "��";
	cats[3].age = 1;
	cats[4].name = "������";
	cats[4].age = 2;
}

void printCat(int selected)
{
	printf("\n\n ==== �� ����̸� �̾Ҵ� ==== \n");
	printf("    �̸�     : %s\n", cats[selected].name);
	printf("    ����     : %d\n", cats[selected].age);
	printf("    ����     : ");
	for (int i = 0; i < cats[selected].age; i++)
	{
		printf("%s", "��");
	}
	printf("\n\n");
}

int checkCollection()
{
	int collectAll = 1;
	printf("\n\n ### ������ ����� ��� ###\n\n");
	for (int i = 0; i < 5; i++)
	{
		if (collect[i] == 0)
		{
			printf("%10s","(�� �ڽ�)");
			collectAll = 0;
		}
		else
		{
			printf("%10s", cats[i].name);
		}
	}
	printf("\n ########################\n\n");

	if (collectAll) // �� ������� if (1)
	{
		printf("\n--- �� ��Ҿ�!---\n\n");		
	}

	return collectAll;
}