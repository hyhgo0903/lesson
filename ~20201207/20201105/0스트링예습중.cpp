#include <iostream>
#include <string>
using namespace std;

char x()
{
	return 'f';
}

int main0000()
{
	string s;
	cout << "cin �Է� : ";
	cin >> s;
	cout << s << endl;
	cin.ignore(); // �Է°����ְ� �ٽ� ����
	cout << "\n";


	cout << "��Ʈ�� �Է� : ";
	getline(cin, s);
	cout << s << endl;
	cout << "\n";

	s = "when in Rome, uunonohu Rome";
	cout << s.find("Rome") << endl; // 8
	cout << s.find("Rome",9) << endl; // 14

	cout << s[9] << endl; // o
	cout << s.empty() << endl; // 0 (false)
	s.insert(9, "etetetet");
	cout << s << endl;

	for (char i : s)
	{
		if (i == 'e') continue;
		cout << i;
	}
	cout << endl ;

	cout << x();

	return 0;
}