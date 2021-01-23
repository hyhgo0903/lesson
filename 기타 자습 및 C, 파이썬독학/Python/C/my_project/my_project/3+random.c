#include <time.h>
// 이것만으로 안되면
// #include <stdlib.h> 도 넣어주면 됨
#include <stdio.h>

int main_rand(void)
{
	printf("--난수초기화 이전--\n");
	// 계속 같은 값이 나옴
	for (int i = 0; i <= 5; i++)
	{
		printf("%d  ", rand() % 10);
		// 0~9값이 뽑히므로 주의
		// 1~10 뽑고싶으면 rand() % 3 + 1 하면 됨
	}

	srand(time(NULL)); // 난수 초기화
	printf("\n--난수초기화 이후--\n");

	for (int i = 0; i <= 5; i++)
	{
		printf("%d  ", rand() % 10);
	}
	return 0;
}