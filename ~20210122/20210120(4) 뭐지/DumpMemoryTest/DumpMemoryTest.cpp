// DumpMemoryTest.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <memory.h>

using namespace std;

int main()
{
#ifdef _DEBUG
	// 종료할 때 덤프메모리를 체크하는 전처리기
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//	MainClass 에 테스트용으로 int* pInt 를 동적할당하고 지우지 않았다
	//	이 상태에서 F5 (로컬 디버그) 으로 실행하게되면 '출력' 탭에
	/*
		Detected memory leaks!
		Dumping objects ->
		(.. 현재 프로젝트 파일) : {232} normal block at 0x007D3C58, 4byte long.
		이라는 문자열이 나온다.

		위 문자열을 더블클릭하면 메모리릭이 발생한 코드를 가리킨다.
		허나 위치가 나타나지 않는 경우도 있는데 중괄호 {232} 내부의 번호를 이용해 찾을 수 있다

		밑의 _CrtSetBreakAlloc() 안에 232 라는 번호를 넣고 로컬 디버그를 실행하면
		해당 메모리릭이 발생한 코드에서 디버깅이 중지된다
	*/
	//_CrtSetBreakAlloc();
#endif

	int* i = new int();

#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
#endif
}
