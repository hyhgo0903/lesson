#include <stdio.h>

/* ���� (�����Լ� ���ʿ���)
�� �Լ��� ���ž� �ϴ°�.
��ȯ�� �Լ��̸�(���ް� = �Ķ����);
��ȯ�� : int / double / float / char..
��ȯ���� �������� void (return �ʿ�X) */
void p(int num);
void func_without_return();
int func_with_return();
void func_with_params(int a, int b, int c);
int minus(int a, int b);

int main_func(void) // �̰� ���ް����� int���� ��ȯ�Ѵ� ����
{
	int num = 5;
	p(num);
	num = num - 1; // 4
	p(num);
	num -= 1; // 3
	p(num);
	num *= 3; // 9
	p(num);
	num /= 3; // 3
	p(num);
	func_without_return();
	int ret = func_with_return();
	p(ret);
	func_with_params(1, 2, 3);
	ret = minus(5, 2);
	p(ret);
	printf("%d - %d = %d\n", 10, 4, minus(10, 4));

	return 0;
}

// ���� (�����Լ� �Ʒ�)
void p(int num) // �̰� �Ȱ����ϵ�, ;�� x
{
	printf("�Է°��� = %d\n", num);
}

void func_without_return()
{
	printf("��ȯ���� ���ް��� ���� �Լ��Դϴ�.\n");
}
int func_with_return()
{
	printf("��ȯ���� �ִ� �Լ��Դϴ�.\n");
	return 10;
}
void func_with_params(int a, int b, int c)
{
	printf("���ް��� �ִ� �Լ��Դϴ�.\n���ް��� %d, %d, %d\n",
		a, b, c);
}
int minus(int a, int b)
{
	printf("��ȯ���� ���ް��� �ִ� �Լ��Դϴ�.\n");
	return a - b;
}