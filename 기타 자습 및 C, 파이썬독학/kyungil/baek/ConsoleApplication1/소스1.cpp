#include <iostream>
#include <string>

using namespace std;

class Point
{
private:
	int x, y;
public:
	Point(int x1, int y1) : x{ x1 }, y{ y1 } {}
	Point(const Point &p2) : x{ p2.x }, y{ p2.y }{}
	int getX() { return x; }
	int getY() { return y; }
};

int main()
{
	Point xx(1,3);
	cout << xx.getY();
	Point yy(xx);
	cout << yy.getY();
	return 0;
}
