#include <iostream>
#include <string>
using namespace std;
void blus(int a){a += 100;}
void clus(int& a){a += 100;}
void dlus(int* b){*b += 100;}

class Dog
{
	string name;
	int age;
public:
	Dog();
	int getAge() { return age; }
	void setAge(int x) { age = x; }
	
};

int main()
{
	int a = 150;
	blus(a); // a��½� 150 : �� �ݿ� �ȵ�
	clus(a); // a��½� 250 : �� �ݿ� ��	
	int *b;			b = &a;
	dlus(b); // �Ű������� �����ͺ��� �ƴϸ� ������
	// a��½� 350 : �� �ݿ� ��

	Dog * dog;
	dog = new Dog;	// �� �� ���ļ� Dog *dog = new Dog; �� ����
	// ������ = new ��������Ÿ��;
	cout << (*dog).getAge() << "\n"; //10
	(*dog).setAge(14); // dog->setAge(14); �� ����
	cout << dog->getAge() << "\n"; // 14
	delete dog;

	return 0;
}

Dog::Dog()
{
	name = "������";
	age = 10;
}
