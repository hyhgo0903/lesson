#include <stdio.h>
#include <time.h>

typedef struct {
	char* name;
	int age;	
} CAT;

//현재까지 보유한 고양이
int collect[5] = { 0,0,0,0,0 };

//전체 고양이 리스트
CAT cats[5];

void initCats(); // 고양이 정보 초기화
void printCat(int selected);
int checkCollection();

int main_struct_project(void)
{
	srand(time(NULL));

	initCats();

	while (1)
	{
		printf("가챠시작! 아무키나 눌러서 확인\n");
		getchar();

		int selected = rand() % 5; // 0~4
		printCat(selected); // 고양이 정보 출력
		collect[selected] = 1; // 고양이 뽑기 처리
		
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
	cats[0].name = "킁킁이";
	cats[0].age = 5;
	cats[1].name = "레오";
	cats[1].age = 3;
	cats[2].name = "쪼롱이";
	cats[2].age = 4;
	cats[3].name = "쮸";
	cats[3].age = 1;
	cats[4].name = "고향이";
	cats[4].age = 2;
}

void printCat(int selected)
{
	printf("\n\n ==== 이 고양이를 뽑았다 ==== \n");
	printf("    이름     : %s\n", cats[selected].name);
	printf("    나이     : %d\n", cats[selected].age);
	printf("    나이     : ");
	for (int i = 0; i < cats[selected].age; i++)
	{
		printf("%s", "★");
	}
	printf("\n\n");
}

int checkCollection()
{
	int collectAll = 1;
	printf("\n\n ### 보유한 고양이 목록 ###\n\n");
	for (int i = 0; i < 5; i++)
	{
		if (collect[i] == 0)
		{
			printf("%10s","(빈 박스)");
			collectAll = 0;
		}
		else
		{
			printf("%10s", cats[i].name);
		}
	}
	printf("\n ########################\n\n");

	if (collectAll) // 다 모은경우 if (1)
	{
		printf("\n--- 다 모았어!---\n\n");		
	}

	return collectAll;
}