#include <iostream>
using namespace std;

int main()
{
	//*
	//**
	//***
	//****
	//*****
	cout << "1��\n";
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
	cout << "2��\n";
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5 - i; j++)
		{
			cout << "*";
		}
		cout << endl;
	}

	//    * ��ĭ4 ��1
	//   **     3   2
	//  ***
	// ****
	//*****
	cout << endl;
	cout << "3��\n";
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

	//***** ��ĭ0 ��5
	// ****     1  4
	//  ***
	//   **
	//    *
	cout << endl;
	cout << "4��\n";
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

	return 0;
}