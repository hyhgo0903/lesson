#include <stdio.h>
#include <time.h>

int array_Animal[4][5];
int checkAnimal[4][5]; // 뒤집혔는지 여부 확인
char* strAnimal[10];
// 포인터형으로 만들었음
// char* sPtr = "동물이름";
// 라고 한다면 "동물이름"이 메모리 공간상에 만들어지고
// sPtr도 그 주소를 갖게됨. 이걸로 쉽게 접근가능

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

	int failCount = 0; // 실패횟수

	while (1)
	{
		int select1 = 0; // 사용자가 선택한 처음수
		int select2 = 0; // 사용자가 선택한 두번째수

		printAnimals(); // 동물위치출력
		printQustion(); // 문제 출력 (카드지도)
		printf("뒤집을 카드를 2개 고르세요 : ");
		scanf_s("%d %d", &select1, &select2);
		if (select1 == select2)
		{
			printf("같은걸 고를 순 없음\n\n");
			continue;
		}

		// 좌표에 해당하는 카드를 뒤집고 같은지 확인
		int firSelect_x = conv_pos_x(select1);
		int firSelect_y = conv_pos_y(select1);

		int secSelect_x = conv_pos_x(select2);
		int secSelect_y = conv_pos_y(select2);

		if (checkAnimal[firSelect_x][firSelect_y]==0
			&& checkAnimal[secSelect_x][secSelect_y] == 0
			// 카드가 뒤집히지 않았는지 여부
			&& array_Animal[firSelect_x][firSelect_y]
			== array_Animal[secSelect_x][secSelect_y])
			//두 동물이 같은지
		
		{
			printf("\n정답! : %s 발견\n\n",
				strAnimal[array_Animal[firSelect_x][firSelect_y]]);
			checkAnimal[firSelect_x][firSelect_y] = 1;
			checkAnimal[secSelect_x][secSelect_y] = 1;
		}
		else // 다른 동물인 경우
		{
			printf("\n틀렸거나 이미 뒤집힌 카드!\n\n");
			printf("%d : %s\n", select1,
				strAnimal[array_Animal[firSelect_x][firSelect_y]]);
			printf("%d : %s\n\n\n", select2,
				strAnimal[array_Animal[secSelect_x][secSelect_y]]);
			failCount++;
		}
		if (foundAllAnimal() == 1)
		{
			printf("\n\n모두 찾았음!\n\n");
			printf("\n\n못맞춘 횟수 %d\n\n",failCount);
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
	strAnimal[0] = "사자";
	strAnimal[1] = "호랑이";
	strAnimal[2] = "토끼";
	strAnimal[3] = "원숭이";
	strAnimal[4] = "하마";
	strAnimal[5] = "고양이";
	strAnimal[6] = "강아지";
	strAnimal[7] = "돼지";
	strAnimal[8] = "코끼리";
	strAnimal[9] = "낙타";
}

void shuffleAnimal()
{ // 20장의 카드에 이름을 섞어서 배치
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
{ // 빈공간 찾기
	while (1)
	{
		int randPos = rand() % 20; // 0~19
		// 1->[0,0] 19 -> [3,4]
		int x = conv_pos_x(randPos);
		int y = conv_pos_y(randPos);

		if (array_Animal[x][y] == -1) // 비어있음
		{
			return randPos;
		}
	}
	return 0; // 이건 의미없음
}

int conv_pos_x(int x)
{// 19 -> [3,4]
	return x / 5;
} // 정수형이라 알아서 버림됨
// 19 -> 3.8(실제값) -> 3
// 11 -> 2.2(실제값) -> 2

int conv_pos_y(int y)
{
	return y % 5;
} // 나머지활용. 19 -> 4, 11->1

void printAnimals()
{
	printf("\n====프로그래밍상출력======\n");
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			printf("%8s", strAnimal[array_Animal[i][j]]);
			// 8칸공간 확보
		}
		printf("\n");
	}
	printf("======================\n");
}
/*
                   seq                checkAnimal
□□□□□    0  1  하마  3  4        0 0 1 0 0
□□□□□    5  6  7  8  9           0 0 0 0 0
□□□□□   10 11 12 하마 14         0 0 0 1 0
□□□□□   15 16 17 18 19           0 0 0 0 0
*/
void printQustion()
{
	printf("\n\n(문제)\n\n");
	int seq = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			// 뒤집어서 정답 맞췄으면 동물이름
			if (checkAnimal[i][j] != 0)
			{
				printf("%8s", strAnimal[array_Animal[i][j]]);
			}
			else
				printf("%8d", seq);
			// 아직 뒤집지 못했으면(정답못맞췄음)
			// 뒷면 -> 위치를 나타내는 숫자
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