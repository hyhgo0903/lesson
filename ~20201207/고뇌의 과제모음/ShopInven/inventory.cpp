#include "inventory.h"
inventory::inventory()
{
}

inventory::~inventory()
{
}

void inventory::inventoryOutput()
{	
	for (int i = 0; i<_vInven.size();i++)
	{
		cout << " ======================= 보유 아이템 =====================" << endl;
		cout << "이  름 : " << _vInven[i].name << endl;
		cout << "성  능 : " << _vInven[i].ability << endl;
		cout << "가  격 : " << _vInven[i].price << endl;
		cout << "설  명 : " << _vInven[i].description << endl;
		cout << "========================================================" << endl;
	}
}

void inventory::inventoryOutput(int itemNum)
{
	for (int i = 0; i < _vInven.size(); i++)
	{
		if (_vInven[i].itemKind != itemNum) continue;

		cout << " ======================= 25기 상점 =====================" << endl;
		cout << "이  름 : " << _vInven[i].name << endl;
		cout << "성  능 : " << _vInven[i].ability << endl;
		cout << "가  격 : " << _vInven[i].price << endl;
		cout << "설  명 : " << _vInven[i].description << endl;
		cout << "========================================================" << endl;
	}
}
void inventory::itemSetup2()
{
	weapon1.itemKind = 1;
	weapon1.name = "뚜의 메모리 검";
	weapon1.description = "근데요... 라고 시동어를 외치면 길이만큼 할당받아 사용된다. (양쌤이 싫어한다)";
	weapon1.ability = 32;
	weapon1.price = 64;
	weapon2.itemKind = 1;
	weapon2.name = "남영이의 동물채찍";
	weapon2.description = "조근하게 죽으라고 귓가에 들린다";
	weapon2.ability = 45;
	weapon2.price = 77;
	weapon3.itemKind = 1;
	weapon3.name = "또의 상한 식빵 (셋트 아이템)";
	weapon3.description = "식중독 도트데미지 주의. 웃으면서 너도 먹을래 권함을 받음 주의";
	weapon3.ability = 40;
	weapon3.price = 1400;
	armor1.itemKind = 2;
	armor1.name = "창훈이의 패딩";
	armor1.description = "하지만 안에 오리털은 널 값이다";
	armor1.ability = 5;
	armor1.price = 10;
	armor2.itemKind = 2;
	armor2.name = "찬호의 백팩";
	armor2.description = "유사시의 방패로 쓸수있다. (안에 전공책 한가득)";
	armor2.ability = 13;
	armor2.price = 50000;
	armor3.itemKind = 2;
	armor3.name = "덕호의 코트";
	armor3.description = "얼죽코";
	armor3.ability = 87;
	armor3.price = 250;
	acce1.itemKind = 3;
	acce1.name = "태준이의 회종시계";
	acce1.description = "거래를 하러왔다 도르마무(스위스 산)";
	acce1.ability = 50;
	acce1.price = 30;
	acce2.itemKind = 3;
	acce2.name = "종환이의 스마트폰";
	acce2.description = "앱등이가 이 악세서리를 싫어합니다";
	acce2.ability = 100;
	acce2.price = 1000;
	acce3.itemKind = 3;
	acce3.name = "현정이의 아이패드";
	acce3.description = "잡스형 세상이 왜 이래";
	acce3.ability = 200;
	acce3.price = 3000;
	potion1.itemKind = 4;
	potion1.name = "종태의 신발맛 포션";
	potion1.description = "냄새만 견디면 효과는 뛰어나다 효과는!!!";
	potion1.ability = 100;
	potion1.price = 100;
	potion2.itemKind = 4;
	potion2.name = "현종이의 (지리산) 수";
	potion2.description = "맑고 깨끗해효 (하지만 아리수가 들었다)";
	potion2.ability = 200;
	potion2.price = 200;
}

void inventory::itemBuy(int x)
{
	switch (x)
	{
	case 0:
		_vInven.push_back(weapon1);
		break;
	case 1:
		_vInven.push_back(weapon2);
		break;
	case 2:
		_vInven.push_back(weapon3);
		break;
	case 3:
		_vInven.push_back(armor1);
		break;
	case 4:
		_vInven.push_back(armor2);
		break;
	case 5:
		_vInven.push_back(armor3);
		break;
	case 6:
		_vInven.push_back(acce1);
		break;
	case 7:
		_vInven.push_back(acce2);
		break;
	case 8:
		_vInven.push_back(acce3);
		break;
	case 9:
		_vInven.push_back(potion1);
		break;
	case 10:
		_vInven.push_back(potion2);
		break;
	}
}
