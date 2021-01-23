#include <stdio.h>
// 2. 피라미드

int main_2pyra(void)
{

	int a;
	printf("층수입력:");
	scanf_s("%d", &a);
	for (int i = 0; i < a; i++)
	{
		for (int j = 0; j < a-i-1; j++)
			printf(" ");
		for (int k = 0; k < 2 * i + 1; k++)
			printf("*");
		printf("\n");
	}
	return 0;
}