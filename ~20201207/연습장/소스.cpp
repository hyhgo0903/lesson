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
	blus(a); // a출력시 150 : 값 반영 안됨
	clus(a); // a출력시 250 : 값 반영 됨	
	int *b;			b = &a;
	dlus(b); // 매개변수에 포인터변수 아니면 오류남
	// a출력시 350 : 값 반영 됨

	Dog * dog;
	dog = new Dog;	// 두 줄 합쳐서 Dog *dog = new Dog; 와 같음
	// 포인터 = new 포인터의타입;
	cout << (*dog).getAge() << "\n"; //10
	(*dog).setAge(14); // dog->setAge(14); 와 같음
	cout << dog->getAge() << "\n"; // 14
	delete dog;

	return 0;
}

Dog::Dog()
{
	name = "개똥이";
	age = 10;
}
