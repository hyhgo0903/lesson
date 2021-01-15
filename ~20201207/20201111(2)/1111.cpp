#include <Windows.h>

// API : Application Programming Interface

HINSTANCE	_hInstance; // 인스턴스. 해당프로그램의 고유번호
// 앞에 h는 핸들의 약자
HWND		_hWnd;		//윈도우 핸들

LPCTSTR		_lpszClass = TEXT("25기");

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
// 함수 프로토타입 선언

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszClass, int cmdShow)
{
	MSG message; // 윈도우 메시지를 담은 구조체
	WNDCLASS wndClass; // 윈도우 클래스 구조체

	_hInstance = hInstance; // 면허증 발급. 고유번호 할당

	wndClass.cbClsExtra = 0; // 클래스의 여분메모리(0이면 안준거)
	//윈도우 클래스 여분 메모리
	wndClass.cbWndExtra = 0; // 윈도우 여분 메모리(0이면 안준거)
	wndClass.hbrBackground = (HBRUSH)GetStockObject(DKGRAY_BRUSH);
	// 윈도우 창 백그라운드 컬러(F12쓰면 있음)
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);	 // 마우스커서 모양(F12쓰면 있음)
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION); // 해당앱의 아이콘 모양
	wndClass.hInstance = hInstance; //인스턴스 등록
	wndClass.lpfnWndProc = (WNDPROC)WndProc; //윈도우 프로시져
	wndClass.lpszClassName = _lpszClass; //윈도우 클래스 등록
	wndClass.lpszMenuName = NULL; // 메뉴 여부
	wndClass.style = CS_HREDRAW | CS_VREDRAW; //윈도우 스타일~
	

	RegisterClass(&wndClass); // 윈도우창 만들 등록을 한 것임

	_hWnd = CreateWindow( //정보를 토대로 윈도우 창 만든다
		_lpszClass,
		_lpszClass,
		WS_OVERLAPPEDWINDOW, //윈도우 창 스타일
		50,//윈도우창 최초의 시작점(시작좌표x)
		50, // y
		800,//윈도우창 최초의 가로크기
		600,//윈도우창 최초의 세로크기
		NULL,
		(HMENU)NULL,
		hInstance,
		NULL);

	ShowWindow(_hWnd, cmdShow); //얘가 있어야 윈도우 창이 나타남

	// GetMessage : 윈도우에서 어떤 메세지가 발생하면 그때 처리함
	// PeekMessage : 메세지가 있든 없든 상시들고있음
	while (GetMessage(&message, 0, 0, 0))
	{
		TranslateMessage(&message);	//윈도우 메시지를 받아옴
		DispatchMessage(&message);	//위에 받아온 메시지를 직접 컴퓨터에게 전달함
	}

	return message.wParam;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	//WPARAM : 키보드 눌르는 것이든, 마우스 좌,우,휠 클릭하면 얘가 감지함
	//(w파라미터)
	//LPARAM : 마우스 좌표를 감지함

	PAINTSTRUCT ps;
	HDC			hdc; // 핸들 디바이스 컨텍스트(화면에 그림을 그려줌)
	// dc환경에서는 0,0이 좌상단 opengl은 좌하단

	switch (iMessage)
	{
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);

		// 기본적으로 2012이후부턴
		// 마소에서 유니코드를 권장한다고 말하고 강요한다
		// 2016이후 카멜식을 권장한다고 말하고 강요한다

		/* 이하 유니코드
		TextOut(hdc, 100, 200, L"2D 입니까?", wcslen(L"2D 입니까?"));
		// 유니코드는 앞에L붙여줌

		SetTextColor(hdc, RGB(255, 0, 0)); // 색상값이 1바이트(언사인드기준 0~255)
		TextOut(hdc, 100, 500, L"빼빼로?", wcslen(L"빼빼로?"));
		TextOut(hdc, 100, 400, L"rsrs?", wcslen(L"rsrs?"));

		SetTextColor(hdc, RGB(255, 0, 255));
		const TCHAR* str = TEXT("내일은 연습장 챙겨오는게 좋을걸?");
		TextOut(hdc, 300, 300, str, wcslen(str));
		*/

		//이하 멀티바이트
		TextOut(hdc, 100, 500, "빼빼로?", strlen("빼빼로?"));

		SetTextColor(hdc, RGB(255, 0, 255)); // 이건 그대로

		const char* str = "우리가 원래 알던 것";
		TextOut(hdc, 300, 300, str, strlen(str));



		//멀티바이트				와이드바이트				유니코드
		//strlen	==		wcslen		==		_tcslen(문자열 길이)
		//strcmp	==		wcscmp		==		_tcscmp(문자열 비교)
		//strcpy	==		wcscpy		==		_tcscpy(문자열 복사)
		//strchr	==		wcschr		==		_tcschr(문자 찾기)
		//strstr	==		wcsstr		==		_tcsstr(문자열 찾기)
		//strcat	==		wcscat		==		_tcscat(문자열 이어붙이기)
		//strtok	==		wcstok		==		_tcstok(문자열 자르기)

		EndPaint(hWnd, &ps);
	}
	break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}