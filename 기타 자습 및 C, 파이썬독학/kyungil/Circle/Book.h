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
	// �̷��� ������ xx yy������ ȣ���ϴ°�
	// ����� �ȵ�.(2���� �ΰ��� �ش��ϹǷ�)
	~Book();
	void print();
	void jojack(); // ������ ���ְ� ����غ�
};

