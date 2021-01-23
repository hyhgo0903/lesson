#include <stdio.h>
#include <time.h>

int lv; // 전역변수 선언
int arrayFish[6];
int* cursor;

void initData();
void printFishes();
void decreaseWater(long a);
int checkFishAlive();

int main_pointer_project(void)
{
	long startTime = 0;
	// long은 시간 정의. 시작시간
	long totalElapsedTime = 0;	// 총 경과 시간
	long prevElapsedTime = 0;
	// 직전 경과 시간(최근 물 준 시간간격)

	int num; // 몇번어항에 물을 줄것인지 입력받음.
	initData();

	cursor = arrayFish;

	startTime = clock();
	// 현재 시간을 millisecond(1/1000초)단위로 반환
	while (1)
	{
		printFishes();
		printf("몇 번 어항에 물? ");
		scanf_s("%d", &num);

		// 입력값 체크
		if (num < 1 || num > 6)
		{
			printf("입력값이 잘못되었습니다.");
			continue;
		}

		totalElapsedTime = (clock() - startTime) / CLOCKS_PER_SEC;
		// clock단위(밀리세컨드)를 초단위로 바꾸기 위해서
		printf("\n\n총 경과시간 : %ld 초\n", totalElapsedTime);

		//직전 물 준 시간(마지막으로 물준시간) 이후 흐른 시간
		prevElapsedTime = totalElapsedTime - prevElapsedTime;
		printf("최근 경과시간 : %ld 초\n", prevElapsedTime);

		// 어항의 물 감소
		decreaseWater(prevElapsedTime);

		// 입력한 어항에 물을 줌
		if (cursor[num - 1] <= 0)
		{
			printf("%d번 물고기는 이미 사망 물주기 취소\n", num);
		}
		else if(cursor[num - 1] +1 <= 100)
		{
			printf("%d번에 물주기\n", num);
			cursor[num - 1] += 1;
		}

		// 레벨을 올릴건지 확인(20초마다)
		if (totalElapsedTime / 20 > lv - 1)
		{
			lv++;
			printf("\n\n####레벨업 %d→%d####\n\n", lv - 1, lv);
			if (lv == 5)
			{
				printf("####최고레벨 달성! 게임 종료\n");
				exit(0);
			}
		}

		//모든 물고기가 죽었는지 확인
		if (checkFishAlive() == 0)
		{
			printf("\n\n####모든 물고기가 죽었다####\n\n");
			exit(0);
		}
		else
		{
			printf("\n한마리 이상 생존 계속 진행\n\n");
		}
		prevElapsedTime = totalElapsedTime;
	}

	return 0;
}

void initData()
{
	lv = 1; // 게임 레벨 (1~5)
	for (int i = 0; i < 6; i++)
	{
		arrayFish[i] = 100; // 어항의 물높이 (0~100)
	}
}
void printFishes()
{
	printf("%3d번 %3d번 %3d번 %3d번 %3d번 %3d번\n", 1, 2, 3, 4, 5, 6);
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
		arrayFish[i] -= (lv * 2 * (int)a); // 2는 난이도 조절 위해
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