#include <stdio.h>
// ����ü ����
struct GameInfo {
	char* name;
	int year;
	int price;

	struct GameInfo* friendGame;
	// ������ü����. ����ü���� ����ü
};

typedef struct {
	char* name;
	int year;
	int price;

	struct GameInfo* friendGame;
} GAME_INFO; // �� �Ʒ��ٿ� ����

int main_struct(void)
{
	// ����ü ���
	struct GameInfo gameInfo1;
	gameInfo1.name = "��������";
	gameInfo1.year = 2017;
	gameInfo1.price = 1000;

	// ����ü ���
	printf("== ���� ��� ���� ==\n");
	printf("���Ӹ�   : %s\n", gameInfo1.name);
	printf("��ÿ��� : %d\n", gameInfo1.year);
	printf("����     : %d\n", gameInfo1.price);

	// ����ü�� �迭ó�� �ʱ�ȭ
	struct GameInfo gameInfo2 = {"�ʵ�����",2020,2000,"�ʵ�ȸ��"};
	printf("== �Ǵٸ� ���� ��� ���� ==\n");
	printf("���Ӹ�   : %s\n", gameInfo2.name);
	printf("��ÿ��� : %d\n", gameInfo2.year);
	printf("����     : %d\n", gameInfo2.price);

	// ����ü �迭
	struct GameInfo gameArray[2] = {
	{"����",2010,5000,"��ȸ"} ,
	{"�ʵ�",2030,7000,"��ȸ"}
	};

	// ����ü ������
	struct GameInfo* gamePtr;
	gamePtr = &gameInfo1;
	printf("\n\n== ������ ���� ==\n");
	printf("���Ӹ�   : %s\n", (*gamePtr).name);
	printf("��ÿ��� : %d\n", (*gamePtr).year);
	printf("����     : %d\n", gamePtr->price);
	// �������϶��� ���Ͱ��� . �Ⱦ��� ȭ��ǥ�� �̿밡��

	//������ü ���ӼҰ�
	gameInfo1.friendGame = &gameInfo2;
	// friendGame�̶�� ����ü ��ü�� ������
	printf("\n\n== ������ü ���� ==\n");
	printf("���Ӹ�   : %s\n", (*gameInfo1.friendGame).name);
	printf("��ÿ��� : %d\n", (*gameInfo1.friendGame).year);
	printf("����     : %d\n", gameInfo1.friendGame->price);

	// typedef
	// �ڷ����� ���� ����
	int i = 1;
	typedef int ����;
	// ���� "����"�� "int"�� �����ϰ� ��밡��
	���� j = 3;
	typedef float �Ǽ�;
	�Ǽ� �Ǽ�����1 = 4.3218f;
	printf("\ni = %d\nj = %d\n�Ǽ�����1 = %.3f\n",
		i, j, �Ǽ�����1);

	typedef struct GameInfo ��������;
	�������� game1; // == struct GameInfo game1;
	game1.name = "�ѱ۰���";
	game1.year = 1991;

	GAME_INFO game2;
	game2.name = "�ѱ۰���2";
	game2.year = 1891;
	// �̷��� �ص� ����
	// �� �̷������� �� ��� struct GameInfo game2;
	// �̷������δ� ���� ����(������ ���)

	return 0;
}