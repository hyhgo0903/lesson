#include <iostream>
using namespace std;

int main()
{
	//*
	//**
	//***
	//****
	//*****
	cout << "1¹ø\n";
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
	cout << "2¹ø\n";
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5 - i; j++)
		{
			cout << "*";
		}
		cout << endl;
	}

	//    * ºóÄ­4 º°1
	//   **     3   2
	//  ***
	// ****
	//*****
	cout << endl;
	cout << "3¹ø\n";
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

	//***** ºóÄ­0 º°5
	// ****     1  4
	//  ***
	//   **
	//    *
	cout << endl;
	cout << "4¹ø\n";
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