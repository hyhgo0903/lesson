#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
int main22222()
{
	int space[30][30];
	int width; // the number of cells on the X axis
	cin >> width; cin.ignore();
	int height; // the number of cells on the Y axis
	cin >> height; cin.ignore();
	for (int i = 0; i < height; i++) {
		string line;
		getline(cin, line);
		for (int j = 0; j < width; j++)
		{
			space[j][i] = line[j];
		}
	}
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (space[j][i] = '0')
			{
				for (int k = j; k < width; k++)
				{
					if (space[k][i] = '0')
					{
						cout << k << " " << i << " ";
						break;
					}
					if (k==width-1)
					{
						cout << "-1 -1 ";
						break;
					}
				}
				for (int k = i; k < height; k++)
				{
					if (space[j][k] = '0')
					{
						cout << j << " " << k << endl;
						break;
					}
					if (k == height - 1)
					{
						cout << "-1 -1\n";
						break;
					}
				}				
			}
		}
	}

	return 0;
}