#include <iostream>
#include <windows.h>

using namespace std;


int main()
{
	HDC hdc = GetWindowDC(GetForegroundWindow());

	Ellipse(hdc, 100, 100, 500, 500);

	return 0;
}
