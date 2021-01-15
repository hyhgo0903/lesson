#include <iostream>

using namespace std;

void output(int);
//함수 전방선언. 가독성을 위해..
// 전방선언이 빠르다? 선조치후보고
//매개변수에 형만 넣어줘도 됨.


class Book
{
public :
	int page = 600;
	const char * name;

	void showPage()
	{
		cout << page << endl;
		cout << name << endl;
	}	
};

int main11()
{
	// 1. 클래스	2. 생성자 3. 소멸자 4. 헤더파일(C++)

	output(1);

	Book comeOn;
	comeOn.name = "어서와";
	comeOn.showPage();



	return 0;
}

void output(int x)
{
	cout << "불금" << endl;
}