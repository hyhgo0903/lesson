#include <stdio.h>
// stdio = standard input/output library

int main_printf(void)
{
	int age = 12;
	printf("%d\n", age);
	// %d�� ���������� ����϶�� �ǹ�. age�� %d��ġ��
	// \n�� �ٹٲ�(end)
	age = 13; // �ռ� int��� ����Ʊ� ������ ����
	printf("%d\n", age);
	/*�ּ� :
	�����������ñ���
	��� ����*/

	float f = 50.5f; // float ���� �� f�� ���ٰ�
	printf("%f\n", f);
	printf("%.2f\n", f);
	// .2�� �Ҽ��� ��°���� ����϶� ��
	double d = 4.428;
	printf("%.2lf\n", d);

	const int year = 1991; // ���
	printf("����: %d\n", year);
	// year = 2001; ���ϸ� ����

	int add = 3 + 7;
	printf("3 + 7 = %d\n", add);
	printf("%d X %d = %d\n", 3, 7, 3 * 7);

	// scanf = Ű�����Է��� �޾Ƽ� ����
	int input;
	printf("���� �Է��ϼ��� : ");
	scanf_s("%d", &input);
	// input�̶� ������ �Է¹ްڴٴ� ��
	printf("�Է°� : %d\n", input);

	int one, two, three;
	printf("3���� ������ �Է��ϼ��� : ");
	scanf_s("%d %d %d", &one, &two, &three);
	printf("1 : %d\n", one);
	printf("2 : %d\n", two);
	printf("3 : %d\n", three);

	char c = 'A';
	printf("%c\n", c);
	// ����char(�ѱ���) ��������ǥ
	char str[256];
	// 256���� ������ ���ڿ�(��������) �����
	printf("���ڿ��� �Է��ϼ��� : ");
	scanf_s("%s", str, sizeof(str));
	// �ص�ǥ�þ��� str
	// �� ū ���ڿ��� �Է¹����� ����ϹǷ�
	// sizeof�� 256�� ������ ���ڴ� �ϴ°�.
	printf("%s\n", str);

	// ������Ʈ : ������ �Լ�
	char name[256];
	printf("�̸�? ");
	scanf_s("%s", name, sizeof(name));

	int age2;
	printf("����? ");
	scanf_s("%d", &age2);
	
	float weight;
	printf("������? ");
	scanf_s("%f", &weight);

	double height;
	printf("Ű? ");
	scanf_s("%lf", &height);

	printf("\n\n --- ���� ---\n\n");
	printf("�̸� :   %s\n", name);
	printf("���� :   %d\n", age2);
	printf("������ : %.2f\n", weight);
	printf("Ű :     %.2lf\n", height);
	return 0;
}