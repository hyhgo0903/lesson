#include <time.h>
// �̰͸����� �ȵǸ�
// #include <stdlib.h> �� �־��ָ� ��
#include <stdio.h>

int main_rand(void)
{
	printf("--�����ʱ�ȭ ����--\n");
	// ��� ���� ���� ����
	for (int i = 0; i <= 5; i++)
	{
		printf("%d  ", rand() % 10);
		// 0~9���� �����Ƿ� ����
		// 1~10 �̰������ rand() % 3 + 1 �ϸ� ��
	}

	srand(time(NULL)); // ���� �ʱ�ȭ
	printf("\n--�����ʱ�ȭ ����--\n");

	for (int i = 0; i <= 5; i++)
	{
		printf("%d  ", rand() % 10);
	}
	return 0;
}