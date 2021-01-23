#include <stdio.h>
void swap(int a, int b);
void swap_add(int * a, int * b);
void changeArray(int* ptr);

int main_pointer2(void)
{
	//배열도 포인터와 닮은점이 있다.
	int arr[3] = { 5,10,15 };
	int* ptr = arr; // ptr은 포인터변수
	for (int i = 0; i < 3; i++)
	{
		printf("배열 arr[%d]의 값: %d\n", i, arr[i]);
	}
	for (int i = 0; i < 3; i++)
	{
		printf("포인터 ptr[%d]의 값: %d\n", i, ptr[i]);
	}
	ptr[0] = 100;
	ptr[1] = 200;
	ptr[2] = 300; // 포인터변수이므로 자체를 바꿈
	for (int i = 0; i < 3; i++)
	{
		printf("배열 arr[%d]의 값: %d\n", i, arr[i]);
		printf("배열 arr[%d]의 값: %d\n", i, *(arr + i));
	}
	/* arr자체는 고유 주소값 가짐 (arr == &arr[0])
	arr 배열의 첫번째 값의 주소와 동일 */
	printf("arr 자체의 값(arr): %d\n", arr);
	printf("arr[0]의 주소(&arr[0]): %d\n", &arr[0]);
	/* "arr + i" 는 arr로부터 i만큼 뒤 주소
	"*(arr + i)"면 이때의 값
	즉 arr[i]는 *(arr + i)와 완전히 동일하다.
	*/
	for (int i = 0; i < 3; i++)
	{
		printf("포인터 ptr[%d]의 값: %d\n", i, ptr[i]);
		printf("포인터 ptr[%d]의 값: %d\n", i, *(ptr + i));
	}

	printf("arr 자체의 값(주소)의 실제 값: %d\n", *arr);
	printf("arr[0] 실제 값: %d\n", *&arr[0]);
	// arr 값 = arr[0]의 주소이므로 (arr == &arr[0])
	// 해당되는 값인 *arr에 대하여
	// *arr = *(arr[0]의 주소) = *&arr[0]
	// *(arr + 0)

	// Swap
	int a = 10;
	int b = 20;
	printf("a = %d, b = %d\n\n", a, b);
	printf("a의 주소 = %d\nb의 주소 = %d\n\n", &a, &b);
	swap(a, b);
	printf("[함수 밖]결과 a = %d, b = %d\n\n", a, b);
	/* 출력시 a, b가 함수 안과 달리 바뀌지 않은 모습.
	
	값에 의한 복사(Call by Value) -> 값만 복사한다는 의미
	swap(10, 20);을 할 때 10,20이라는 값만 던져줬을 뿐
		a와 b 자체를 던져준 건 아님.
	 => 메모리 공간에 있는 주소값 자체를 넘기면?(미션맨)
	*/
	printf("\n\na의 주소 = %d\nb의 주소 = %d\n\n", &a, &b);
	swap_add(&a, &b);
	printf("[함수 밖]결과 a = %d, b = %d\n\n", a, b);

	int arr2[3] = { 10,20,30 };
	changeArray(arr2);

	/* 배열일때 arr2 자체가 주소
	changeArray(&arr[0]);과 동일
	고로 매개변수에 &를 붙일필요 없이 arr2를 넣으면
	주소를 넣은것이 됨.	
	*/
	for (int i = 0; i < 3; i++)
	{
		printf("%d\n", arr2[i]);
	}

	// scanf_s에서 숫자는 &를 쓴 이유: 주소를 참고해야하므로

	return 0;
}

void swap(int a, int b)
{
	printf("[함수 안]a = %d, b = %d\n\n", a, b);
	printf("[함수 안]\na의 주소 = %d\nb의 주소 = %d\n\n", &a, &b);
	int temp = a;
	a = b;
	b = temp;
	printf("[함수 안]결과 a = %d, b = %d\n\n", a, b);
}

void swap_add(int * a, int * b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
	printf("[함수 안]결과 a = %d, b = %d\n\n", *a, *b);
}

void changeArray(int * ptr)
{
	ptr[2] = 50;
}