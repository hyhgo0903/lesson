#include <Windows.h>

HINSTANCE	_hInstance;
HWND		_hWnd;
LPCTSTR		_lpszClass = TEXT("25±â");

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszClass, int cmdShow)
{
	MSG		message;
	WNDCLASS wndClass;

	_hInstance = hInstance;

	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = (WNDPROC)WndProc;
	wndClass.lpszClassName = _lpszClass;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wndClass);

	_hWnd = CreateWindow(
		_lpszClass,
		_lpszClass,
		WS_OVERLAPPEDWINDOW,
		50,
		50,
		500,
		500,
		NULL,
		(HMENU)NULL,
		hInstance,
		NULL);

	ShowWindow(_hWnd, cmdShow);
	while (GetMessage(&message, 0, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	return message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{

	PAINTSTRUCT ps;
	HDC			hdc;

	switch (iMessage)
	{
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);

		for (int i = 0; i < 2; i++)
		{
			Ellipse(hdc, 50 + 25 * i, 50 + 25 * i, 350 - 25 * i, 350 - 25 * i);
		}
		MoveToEx(hdc, 200, 75, NULL);
		LineTo(hdc, 200 - 108, 75 + 186);
		LineTo(hdc, 200 + 108, 75 + 186);
		LineTo(hdc, 200, 75);

		MoveToEx(hdc, 200, 324, NULL);
		LineTo(hdc, 200 - 108, 324 - 186);
		LineTo(hdc, 200 + 108, 324 - 186);
		LineTo(hdc, 200, 324);

		EndPaint(hWnd, &ps);
	}
	break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}