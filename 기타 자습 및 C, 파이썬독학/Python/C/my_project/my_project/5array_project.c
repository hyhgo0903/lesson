#include <stdio.h>
#include <time.h>

int main_array_project(void)
{
	srand(time(NULL));
	printf("\n\n === 발모제 === \n\n");
	int answer;
	int treatment = rand() % 4; // 발모제선택(0~3)

	int cntShowBottle = 0; // 보여줄 병 갯수
	int prevCntShowBottle = 0;// 앞게임에 보여준 병 갯수
	// 서로 보여주는 병갯수 달라서 정답률↑

	for (int i = 1; i <= 3; i++)
	{
		int bottle[4] = { 0,0,0,0 }; // 병 4개
		do {
			cntShowBottle = rand() % 2 + 2; // 2~3
		} while (cntShowBottle == prevCntShowBottle);
		// 같으면 다른수 뽑을때까지 while에서 못 벗어남
		prevCntShowBottle = cntShowBottle;
		// 두개보여줬는데 또 두개보여주지 않도록

		int isincluded = 0; // 발모제포함여부
		printf("%d번째 시도 : ", i);

		//보여줄 병 종류 선택
		for (int j = 0; j < cntShowBottle; j++)
		{
			int randBottle = rand() % 4; // 0~3

			// 아직 선택되지 않은 병이면 선택처리
			if (bottle[randBottle] == 0)
			{
				bottle[randBottle] = 1;
				if (randBottle == treatment)
				{
					isincluded = 1;
				}
			}
			// 선택된 병이면 다시 선택
			else
			{
				j--;
			}
		}
		// 사용자에게 문제 표시
		for (int k = 0; k < 4; k++)
		{
			if (bottle[k] == 1)
				printf("%d ", k + 1);
		}
		printf("물약을 머리에 바릅니다.\n\n");
		if (isincluded == 1)
		{
			printf("머리가 자람\n");
		}
		else
		{
			printf("머리가 자라지 않음\n");
		}

		printf("\n>> 계속하려면 아무키나 누르세요\n");
		getchar(); // 사용자에게 키를 입력받을때까지
		// 대기하는 함수
	}

	printf("\n발모제는 몇번일까요?\n");
	scanf_s("%d", &answer);

	if (answer == treatment + 1)
	{
		printf("\n정답!\n");
	}
	else
	{
		printf("\n오답! 정답은 %d\n", treatment + 1);
	}
	return 0;
}