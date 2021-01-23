#include <iostream>

using namespace std;

class Date
{
	int month, day;
public:
	Date(int a = 1, int b = 1)
	{
		month = a;
		day = b;
	}
	~Date();

	int getMonth()	{return month;}
	int getDay() { return day; }
};


bool same(Date a, Date b)
{
	return a.getDay() == b.getDay() && a.getMonth() == b.getMonth();
}

int main()
{
	Date a(12, 25);
	Date b(1,1);
	Date c(12, 25);
	Date d;

	cout << same(a, b) << endl;
	cout << same(a, c) << endl;
	cout << same(b, d) << endl;

	return 0;
}

Date::~Date()
{
}
