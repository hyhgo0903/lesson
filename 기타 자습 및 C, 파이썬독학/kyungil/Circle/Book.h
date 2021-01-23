#pragma once
class Book
{
private:
	
public:
	int x;
	int y;
	int radius;
	Book();
	Book(int xx);
	Book(int xx, int yy, int zz = 500);
	// 이렇게 했으면 xx yy만으로 호출하는걸
	// 만들면 안됨.(2개면 두개에 해당하므로)
	~Book();
	void print();
	void jojack(); // 참조자 없애고 출력해봐
};

