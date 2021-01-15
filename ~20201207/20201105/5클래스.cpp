#include <iostream>
#include <string>
using namespace std;

class Point {
	double xval, yval;
public:

	static int ccount;
	Point(double x =0.0, double y =0.0)
		:xval(x), yval(y) {
		ccount++;
	}
	double getX() { return xval; }
	double getY() { return yval; }
	Point(Point &other)
	{
		ccount++;
		xval = other.xval;
		yval = other.yval;
	}

	~Point() { ccount--; }
};

void pointSwap(Point &a, Point &b)
{
	Point temp;
	temp = a;
	a = b;
	b = temp;
}

void pointSwapFake(Point a, Point b)
{
	Point temp;
	temp = a;
	a = b;
	b = temp;
}

int Point::ccount = 0;

int main()
{
	Point a(25., 26.);
	Point b;
	Point c(17.,19.);
	b = a; // ���� ����
	cout << b.getX() <<"\n"; //25
	cout << Point::ccount << "\n"; // a,b,c��������� 3

	pointSwap(b,c);
	cout << Point::ccount << "\n"; // 4
	// �Ҷ����� ������ �ֳĸ� temp�� ����� ����

	cout << b.getX() << "\n";  //17
	pointSwapFake(b, c);
	cout << Point::ccount << "\n"; // 7 (����� �����߱� ������ b,c,temp�� �� ������)
	cout << b.getX() << "\n"; // 17 �ȹٲ����

	Point d(b); // ���� ����
	cout << d.getX() << "\n"; // 17
	Point(d);

	cout << Point::ccount << "\n"; // 8


	return 0;
}
