#include <iostream>
// 쉬프트알트클릭: 한번에 여러줄 타이핑

#include "SkeletonWarrior.h"
// 붕어빵틀이 아니라 붕어빵을 줘야
#include "Necromancer.h"

using namespace std;

//getter : 접근자
//setter : 설정자

int main()
{
	SkeletonWarrior sw;
	// 부모클래스 생성자가 먼저.
	
	// 정적할당(Stack이란 메모리 공간에 잡힘)
	// 컴파일러 단계 이전부터 메모리에 잡고 들어옴
	// RunTime도중 메모리 해제 불가

	SkeletonWarrior* sw1 = new SkeletonWarrior;
	// 타입* 포인터이름 = new 타입;
	// 동적할당(Heap이란 메모리 공간에 잡힘)
	// 느림 << 메모리할당 위치를 잡아야하기때문
	// 컴파일러 단계 후 힙이란 곳에서 메모리 빌려옴
	// RunTime도중 메모리 해제 가능,, 느린데도 쓰는이유
	sw1->output(); // ->이렇게 된게 포인터임
	delete sw1; // 메모리 공간을 반환하는 것. 소멸자불러냄
	
	sw.racePassive();
	sw.Qskill();
	sw.Wskill();


	cout << "\n";

	Necromancer necro;
	// 부모클래스 생성자의 아웃풋이 먼저 출력된다.

	necro.racePassive();
	necro.Qskill();
	necro.Wskill();


	return 0;
}