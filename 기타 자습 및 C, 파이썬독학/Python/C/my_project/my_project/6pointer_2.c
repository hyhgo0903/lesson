#include <stdio.h>
void swap(int a, int b);
void swap_add(int * a, int * b);
void changeArray(int* ptr);

int main_pointer2(void)
{
	//�迭�� �����Ϳ� �������� �ִ�.
	int arr[3] = { 5,10,15 };
	int* ptr = arr; // ptr�� �����ͺ���
	for (int i = 0; i < 3; i++)
	{
		printf("�迭 arr[%d]�� ��: %d\n", i, arr[i]);
	}
	for (int i = 0; i < 3; i++)
	{
		printf("������ ptr[%d]�� ��: %d\n", i, ptr[i]);
	}
	ptr[0] = 100;
	ptr[1] = 200;
	ptr[2] = 300; // �����ͺ����̹Ƿ� ��ü�� �ٲ�
	for (int i = 0; i < 3; i++)
	{
		printf("�迭 arr[%d]�� ��: %d\n", i, arr[i]);
		printf("�迭 arr[%d]�� ��: %d\n", i, *(arr + i));
	}
	/* arr��ü�� ���� �ּҰ� ���� (arr == &arr[0])
	arr �迭�� ù��° ���� �ּҿ� ���� */
	printf("arr ��ü�� ��(arr): %d\n", arr);
	printf("arr[0]�� �ּ�(&arr[0]): %d\n", &arr[0]);
	/* "arr + i" �� arr�κ��� i��ŭ �� �ּ�
	"*(arr + i)"�� �̶��� ��
	�� arr[i]�� *(arr + i)�� ������ �����ϴ�.
	*/
	for (int i = 0; i < 3; i++)
	{
		printf("������ ptr[%d]�� ��: %d\n", i, ptr[i]);
		printf("������ ptr[%d]�� ��: %d\n", i, *(ptr + i));
	}

	printf("arr ��ü�� ��(�ּ�)�� ���� ��: %d\n", *arr);
	printf("arr[0] ���� ��: %d\n", *&arr[0]);
	// arr �� = arr[0]�� �ּ��̹Ƿ� (arr == &arr[0])
	// �ش�Ǵ� ���� *arr�� ���Ͽ�
	// *arr = *(arr[0]�� �ּ�) = *&arr[0]
	// *(arr + 0)

	// Swap
	int a = 10;
	int b = 20;
	printf("a = %d, b = %d\n\n", a, b);
	printf("a�� �ּ� = %d\nb�� �ּ� = %d\n\n", &a, &b);
	swap(a, b);
	printf("[�Լ� ��]��� a = %d, b = %d\n\n", a, b);
	/* ��½� a, b�� �Լ� �Ȱ� �޸� �ٲ��� ���� ���.
	
	���� ���� ����(Call by Value) -> ���� �����Ѵٴ� �ǹ�
	swap(10, 20);�� �� �� 10,20�̶�� ���� �������� ��
		a�� b ��ü�� ������ �� �ƴ�.
	 => �޸� ������ �ִ� �ּҰ� ��ü�� �ѱ��?(�̼Ǹ�)
	*/
	printf("\n\na�� �ּ� = %d\nb�� �ּ� = %d\n\n", &a, &b);
	swap_add(&a, &b);
	printf("[�Լ� ��]��� a = %d, b = %d\n\n", a, b);

	int arr2[3] = { 10,20,30 };
	changeArray(arr2);

	/* �迭�϶� arr2 ��ü�� �ּ�
	changeArray(&arr[0]);�� ����
	��� �Ű������� &�� �����ʿ� ���� arr2�� ������
	�ּҸ� �������� ��.	
	*/
	for (int i = 0; i < 3; i++)
	{
		printf("%d\n", arr2[i]);
	}

	// scanf_s���� ���ڴ� &�� �� ����: �ּҸ� �����ؾ��ϹǷ�

	return 0;
}

void swap(int a, int b)
{
	printf("[�Լ� ��]a = %d, b = %d\n\n", a, b);
	printf("[�Լ� ��]\na�� �ּ� = %d\nb�� �ּ� = %d\n\n", &a, &b);
	int temp = a;
	a = b;
	b = temp;
	printf("[�Լ� ��]��� a = %d, b = %d\n\n", a, b);
}

void swap_add(int * a, int * b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
	printf("[�Լ� ��]��� a = %d, b = %d\n\n", *a, *b);
}

void changeArray(int * ptr)
{
	ptr[2] = 50;
}