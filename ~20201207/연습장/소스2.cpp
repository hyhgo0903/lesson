#include <iostream>
using namespace std;

class Point {
	int x, y;
public:
	Point(int x = 20, int y = 20) : x(x), y(y) {}
	void setX(int x) { this->x = x; }
	void setY(int y) { this->y = y; }
	int getX() { return x; }
	int getY() { return y; }
};

int main()
{
	unique_ptr<Point> p(new Point(100, 200));
	// Point *p = new p(100,200); 의 스마트 포인터
	p->setX(30);	(*p).setY(60);
	cout << p->getX() << "\n";

	Point * pp = new Point[100];

	delete[] pp;

	return 0;
}
