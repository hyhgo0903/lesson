#include <iostream>
#include <time.h>

using namespace std;

int main15125211251()
{
	// 배열
	// 같은 변수의 연속적인 나열
	int bullet[10]; // 배열선언[배열갯수]
	// bullet[0~9] bullet[10]는 없으니 주의
	
	for (int i = 0; i < 10; i++)
	{
		bullet[i] = i + 1;
	}
	for (int i = 0; i < 10; i++)
	{
		cout << bullet[i] << "번째 총알\n";
	}
	/* bullet -> 100번지라고 치면
	bullet[0] 100 + sizeof(int)*0 번지에 저장
	bullet[1] 100 + sizeof(int)*1
	bullet[2] 100 + sizeof(int)*2
	bullet[3] 100 + sizeof(int)*3
	.
	.
	.	*/	   
	for (int i : bullet)
	{
		cout << i << " ";
	}
	cout << "\n";

	// 이중배열 (<->단배열,,)
	// 취향껏,, 속도도 같다고 함(원래는 단배열이 빨랐는데)
	int num[3][3];

	// num[0][0], [0][1] ,... [2][2]로 들어온다.
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			num[i][j] = i * j + 5;
		}
	}

	int num2[] = { 0,2,3,5,15 }; // 배열개수([5])가 오토로 들어감
	// (게임계에선 잘 안쓰는 방식임. 개수정도는 알아놓고..)
	int num3[10] = { 0,2,3 }; // 안쓰는 값(num[3]부터..은 쓰레기값이 아니라 0이 들어감

	// shuffle 알고리즘
	srand(time(NULL));
	for (int i = 0; i < 10; i++)
	{
		num3[i] = i + 1;
	}


	int dest, sour, temp;
	for (int i = 0; i < 100; i++) // 100번 자리바꾸기(섞기)
	{
		dest = rand() % 10; // 0~9 방갯수대로
		sour = rand() % 10;
		temp = num3[dest]; // << 스왑하려면 temp가 필요하다.
		//(컴퓨터는 맞바꾸기를 할 줄 모름)
		num3[dest] = num3[sour]; // 자리 바꾸기
		num3[sour] = temp; // 저장된 값 넣기
	}


	for (int i = 0; i < 10; i++)
	{
		cout << num3[i] << "\n";
	}


	return 0;
}