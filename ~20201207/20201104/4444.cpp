#include <iostream>
#include <string>

using namespace std;

int main444()
{
	// 문자열 함수
	// 1. strlen == string length 줄임말
	// 문자열 길이를 정수로 반환

	char name[6] = "teemo";
	char name2[10] = "teemo";
	
	int num = strlen(name);
	int num2 = strlen(name2);

	cout << "문자열 길이 : " << num << endl;
	cout << "문자열 길이 : " << num2 << endl;
	// name배열자체 크기를 읽는게 아님

	// 2. strcmp == string compare 줄임말
	// 문자열 크기를 비교하여 같으면 0,
	// 왼쪽이 크면 1, 오른쪽이 크면 -1을 반환

	char str1[10] = "abc";
	char str2[10] = "def";
	num = strcmp(str1, str2);
	cout << "결과 값은 : " << num << endl;

	// 3. strcat
	// 문자열 이어붙이기
	// strcat(문자열1,문자열2)
	// 단, 문자열 1은 문자열2를
	//받아줄만큼 버퍼가 있어야

	char str3[128] = "home ";
	char str4[50] = "sweet home";
	// strcat(str3, str4); 요러면 에러뜬다.
	strcat_s(str3, str4);

	cout << str3 << endl;

	// 4. strcpy == string copy의 줄임말
	// strcpy(문자열1,문자열2)
	// 문자열1에 2를 복사한다.
	char str5[10];
	char str6[10] = "sorsor";

	strcpy_s(str5, str6);

	cout << str5 << endl;

	char str7[128];
	/*
	cout << "입력 : ";
	cin >> str7;
	for (int i = strlen(str7); i >= 0; i--)
	{
		cout << str7[i];
	}*/

	// 1. 문자열을 입력받아서 짝수번쨰 문자만 뒤집어보세요.
	// ex ) a b c d e -> a d c b e
	// ex2) a b c d e f -> a f c d e b

	char strQuiz[128];
	cout << "입력 : ";
	cin >> strQuiz;

	for (int i = 0; i < strlen(strQuiz); i++)
	{
		if (i % 2 == 1) // 1,3,5,7,9... ->   
		{
			cout << strQuiz[strlen(strQuiz)/2*2 - i];
			// why? : 정수를 2나누고 2곱하는 연산을 하면 홀수의 경우 알아서 1이 빠짐
			// 모범답안 : cout << strQuiz[strlen(strQuiz) - i - (strlen(strQuiz)%2)];
		}
		else
		{
			cout << strQuiz[i];
		}
	}



	cout << endl << endl;
	// 2. strtok_s <-- 조사해보세요.
	// 문자열에서 지정한 문자로 문자열을 분리.
	char 문자열[] = "abc,etqef,jnonjfbghi";
	char 구분자[] = ","; // 구분자
	char *나머지저장됨;
	char *포인터토큰 = strtok_s(문자열,구분자, &나머지저장됨);

	while (나머지저장됨 != NULL)
	{

	}
	cout << *포인터토큰 << endl;
	포인터토큰 = strtok_s(NULL, 구분자, &나머지저장됨);

	// 앞 문자열을 그대로 쓸거면 NULL
	cout << *포인터토큰 << endl;
	포인터토큰 = strtok_s(NULL, 구분자, &나머지저장됨);
	cout << *포인터토큰 << endl;
	//3. 
	// 과제떄 쓴건 _getch()

	//scanf()
	//gets()
	//cin.ignore()
	//cin.getline()

	return 0;
}
