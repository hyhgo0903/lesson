#include <stdio.h>
#include <time.h>
// 3. ���شٿ�

int main(void)
{
	srand(time(NULL));
	int answer = (rand() % 100 )+ 1;
	int input;
	int chance;
	printf("��ȸ �Է�: ");
	scanf_s("%d", &chance);
	while (1)
	{
		if (chance == 0)
		{
			printf("\n\n��ȸ ��� ����!\n\n");
			break;
		}
		printf("\n���� ��ȸ: %d", chance);
		printf("\n\n���纸����: ");
		scanf_s("%d", &input);
		if (input == answer)
		{
			printf("\n\n����!\n\n");
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