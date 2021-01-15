#include <iostream>
#include "arraySample.h"

using namespace std;

void main()
{
	arraySample<int> arrInt;
	arrInt.push_back(1);

	for (int i = 0; i < 10; i++)
	{
		arrInt.push_back(i * 10);
	}

	for (int i = 0; i < arrInt.GetSize(); i++)
	{
		cout << arrInt[i] << endl;
	}


	arraySample<float> arrF;

	arrF.push_back(177.3f);
	arrF.push_back(168.7f);

	for (int i = 0; i < arrF.GetSize(); i++)
	{
		cout << arrF[i] << endl;
	}

	arraySample<const char*> arrS;

	arrS.push_back("°ð Á¡½É");
	arrS.push_back("³Ê³× ¹¹¸Ô?");

	for (int i = 0; i < arrS.GetSize(); i++)
	{
		cout << arrS[i] << endl;
	}
}