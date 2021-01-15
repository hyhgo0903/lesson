#include <iostream>
using namespace std;

int main35113()
{	
	//*
	//**
	//***
	//****
	//*****
	cout << "1번\n";
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < i + 1; j++)
		{
			cout << "*";
		}
		cout << endl;
	}
	
	//*****
	//****
	//***
	//**
	//*
	cout << endl;
	cout << "2번\n";
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5 - i; j++)
		{
			cout << "*";
		}
		cout << endl;
	}
	
	//    * 빈칸4 별1
	//   **     3   2
	//  ***
	// ****
	//*****
	cout << endl;
	cout << "3번\n";
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 4 - i; j++)
		{
			cout << " ";
		}
		for (int j = 0; j < i + 1; j++)
		{
			cout << "*";
		}
		cout << endl;
	}

	//***** 빈칸0 별5
	// ****     1  4
	//  ***
	//   **
	//    *
	cout << endl;
	cout << "4번\n";
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < i; j++)
		{
			cout << " ";
		}
		for (int j = 0; j < 5 - i; j++)
		{
			cout << "*";
		}
		cout << endl;
	}
	/*
	for (i = 0; i<5; i++)
	{
		for (int j = 0; j<5; j++)
		{
			if (3-j > i)
				cout " ";
			else
				cout "*";
		}
	}

	for (i = 0; i<5; i++)
	{
		for (int j = 0; j<5; j++)
		{
			(j<i)? cout << " " : cout "*";
		}
		cout << endl;
	}
	*/
	// 조건문으로도 가능(for문 안쓰고)

	return 0;
}