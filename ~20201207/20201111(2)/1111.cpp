#include <Windows.h>

// API : Application Programming Interface

HINSTANCE	_hInstance; // �ν��Ͻ�. �ش����α׷��� ������ȣ
// �տ� h�� �ڵ��� ����
HWND		_hWnd;		//������ �ڵ�

LPCTSTR		_lpszClass = TEXT("25��");

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
// �Լ� ������Ÿ�� ����

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszClass, int cmdShow)
{
	MSG message; // ������ �޽����� ���� ����ü
	WNDCLASS wndClass; // ������ Ŭ���� ����ü

	_hInstance = hInstance; // ������ �߱�. ������ȣ �Ҵ�

	wndClass.cbClsExtra = 0; // Ŭ������ ���и޸�(0�̸� ���ذ�)
	//������ Ŭ���� ���� �޸�
	wndClass.cbWndExtra = 0; // ������ ���� �޸�(0�̸� ���ذ�)
	wndClass.hbrBackground = (HBRUSH)GetStockObject(DKGRAY_BRUSH);
	// ������ â ��׶��� �÷�(F12���� ����)
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);	 // ���콺Ŀ�� ���(F12���� ����)
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION); // �ش���� ������ ���
	wndClass.hInstance = hInstance; //�ν��Ͻ� ���
	wndClass.lpfnWndProc = (WNDPROC)WndProc; //������ ���ν���
	wndClass.lpszClassName = _lpszClass; //������ Ŭ���� ���
	wndClass.lpszMenuName = NULL; // �޴� ����
	wndClass.style = CS_HREDRAW | CS_VREDRAW; //������ ��Ÿ��~
	

	RegisterClass(&wndClass); // ������â ���� ����� �� ����

	_hWnd = CreateWindow( //������ ���� ������ â �����
		_lpszClass,
		_lpszClass,
		WS_OVERLAPPEDWINDOW, //������ â ��Ÿ��
		50,//������â ������ ������(������ǥx)
		50, // y
		800,//������â ������ ����ũ��
		600,//������â ������ ����ũ��
		NULL,
		(HMENU)NULL,
		hInstance,
		NULL);

	ShowWindow(_hWnd, cmdShow); //�갡 �־�� ������ â�� ��Ÿ��

	// GetMessage : �����쿡�� � �޼����� �߻��ϸ� �׶� ó����
	// PeekMessage : �޼����� �ֵ� ���� ��õ������
	while (GetMessage(&message, 0, 0, 0))
	{
		TranslateMessage(&message);	//������ �޽����� �޾ƿ�
		DispatchMessage(&message);	//���� �޾ƿ� �޽����� ���� ��ǻ�Ϳ��� ������
	}

	return message.wParam;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	//WPARAM : Ű���� ������ ���̵�, ���콺 ��,��,�� Ŭ���ϸ� �갡 ������
	//(w�Ķ����)
	//LPARAM : ���콺 ��ǥ�� ������

	PAINTSTRUCT ps;
	HDC			hdc; // �ڵ� ����̽� ���ؽ�Ʈ(ȭ�鿡 �׸��� �׷���)
	// dcȯ�濡���� 0,0�� �»�� opengl�� ���ϴ�

	switch (iMessage)
	{
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);

		// �⺻������ 2012���ĺ���
		// ���ҿ��� �����ڵ带 �����Ѵٰ� ���ϰ� �����Ѵ�
		// 2016���� ī����� �����Ѵٰ� ���ϰ� �����Ѵ�

		/* ���� �����ڵ�
		TextOut(hdc, 100, 200, L"2D �Դϱ�?", wcslen(L"2D �Դϱ�?"));
		// �����ڵ�� �տ�L�ٿ���

		SetTextColor(hdc, RGB(255, 0, 0)); // ������ 1����Ʈ(����ε���� 0~255)
		TextOut(hdc, 100, 500, L"������?", wcslen(L"������?"));
		TextOut(hdc, 100, 400, L"rsrs?", wcslen(L"rsrs?"));

		SetTextColor(hdc, RGB(255, 0, 255));
		const TCHAR* str = TEXT("������ ������ ì�ܿ��°� ������?");
		TextOut(hdc, 300, 300, str, wcslen(str));
		*/

		//���� ��Ƽ����Ʈ
		TextOut(hdc, 100, 500, "������?", strlen("������?"));

		SetTextColor(hdc, RGB(255, 0, 255)); // �̰� �״��

		const char* str = "�츮�� ���� �˴� ��";
		TextOut(hdc, 300, 300, str, strlen(str));



		//��Ƽ����Ʈ				���̵����Ʈ				�����ڵ�
		//strlen	==		wcslen		==		_tcslen(���ڿ� ����)
		//strcmp	==		wcscmp		==		_tcscmp(���ڿ� ��)
		//strcpy	==		wcscpy		==		_tcscpy(���ڿ� ����)
		//strchr	==		wcschr		==		_tcschr(���� ã��)
		//strstr	==		wcsstr		==		_tcsstr(���ڿ� ã��)
		//strcat	==		wcscat		==		_tcscat(���ڿ� �̾���̱�)
		//strtok	==		wcstok		==		_tcstok(���ڿ� �ڸ���)

		EndPaint(hWnd, &ps);
	}
	break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}