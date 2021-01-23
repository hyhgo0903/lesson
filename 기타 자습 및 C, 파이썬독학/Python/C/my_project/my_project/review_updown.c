#include <stdio.h>
#include <time.h>
// 3. 업앤다운

int main(void)
{
	srand(time(NULL));
	int answer = (rand() % 100 )+ 1;
	int input;
	int chance;
	printf("기회 입력: ");
	scanf_s("%d", &chance);
	while (1)
	{
		if (chance == 0)
		{
			printf("\n\n기회 모두 소진!\n\n");
			break;
		}
		printf("\n남은 기회: %d", chance);
		printf("\n\n맞춰보세요: ");
		scanf_s("%d", &input);
		if (input == answer)
		{
			printf("\n\n정답!\n\n");
			break;
		}
		if (input > answer)
		{
			printf("down\n\n");
		}
		if (input < answer)
		{
			printf("up\n\n");
		}
		chance--;
	}
		
	



	return 0;
}