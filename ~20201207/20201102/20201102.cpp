#include <iostream>
#include <time.h> // rand()함수 위해
using namespace std;

int main2232()
{
	// 1. if문
	int score; //점수용 변수
	cout << "당신의 승점은 ? : ";
	cin >> score;
	if (score >= 40) // 세미콜론 안들어감 주의
	{
		cout << "골드\n";
	}
	else if (score < 40 && score >= 30)
	{
		cout << "실버\n";
	}
	else if (score < 30 && score >= 20)
	{ // else if는 얼마든지 들어올 수 있음.
		cout << "브론즈\n";
		cout << "심해시작\n";
	}
	else
	{
		cout << "아이언\n";
	}
	// if만 여러번 있는것보다 else if, else 쓰는게 연산속도가 빠르다
	// why? 하나 찾으면 이하 else, else if구문은 검사할 필요가 없으므로

	// 프로젝트에는 사용할수 있는 조건문의 갯수가 정해져있다
	//(예전 기준.. 지금은 어떨지 모름)


	// 2. switch문
	// 정수랑 열거형만 가능 (float를 넣으면 에러)
	// 가독성 때문에 많이 쓴다.

	srand(time(NULL));

	//int num = rand() % 5; // 0~4
	//switch (num)
	//{
	//	case 0:
	//		cout << "랜덤으로 나온 숫자는 0 입니다.\n";
	//	break;
	//	case 1:
	//		cout << "랜덤으로 나온 숫자는 1 입니다.\n";
	//	break;
	//	case 2:
	//		cout << "랜덤으로 나온 숫자는 2 입니다.\n";
	//	break;
	//	case 3:
	//		cout << "랜덤으로 나온 숫자는 3 입니다.\n";
	//	break;
	//	case 4:
	//		cout << "랜덤으로 나온 숫자는 4 입니다.\n";
	//	break;
	//}

	//int selectNum;

	//cout << "플레이할 챔피언을 고르세요.\n";
	//cout << "1. 티모, 2. 야스오, 3. 요네, 4. 베인\n";

	//switch (selectNum)
	//{
	//	case 1:
	//		cout << ".\n";
	//	break;
	//	case 2:

	//	break;
	//	case 3:

	//	break;
	//	case 4:

	//	break;
	//	default:
	//		cout << "마스터이를 고르셨습니다.\n";
	//	break;
	//}

	// 삼항연산자
	// 조건? 참: 거짓
	int num = 3;
	num == 3 ? cout << "맞음" : cout << "아님";
	// 깔끔해보이는 효과? 근데 굳이?
	



	return 0;
}
