#include "shop.h"

shop::shop()
{
}


shop::~shop()
{
}

void shop::itemSetup()
{
	tagItemInfo weapon1;
	weapon1.itemKind = ITEM_WEAPON;
	weapon1.name = "1. 뚜의 메모리 검";
	weapon1.description = "근데요... 라고 시동어를 외치면 길이만큼 할당받아 사용된다. (양쌤이 싫어한다)";
	weapon1.ability = 32;
	weapon1.price = 64;

	_vItem.push_back(weapon1);

	tagItemInfo weapon2;
	weapon2.itemKind = ITEM_WEAPON;
	weapon2.name = "2. 남영이의 동물채찍";
	weapon2.description = "조근하게 죽으라고 귓가에 들린다";
	weapon2.ability = 45;
	weapon2.price = 77;

	_vItem.push_back(weapon2);

	tagItemInfo weapon3;
	weapon3.itemKind = ITEM_WEAPON;
	weapon3.name = "3. 또의 상한 식빵 (셋트 아이템)";
	weapon3.description = "식중독 도트데미지 주의. 웃으면서 너도 먹을래 권함을 받음 주의";
	weapon3.ability = 40;
	weapon3.price = 1400;

	_vItem.push_back(weapon3);

	tagItemInfo armor1;
	armor1.itemKind = ITEM_ARMOR;
	armor1.name = "1. 창훈이의 패딩";
	armor1.description = "하지만 안에 오리털은 널 값이다";
	armor1.ability = 5;
	armor1.price = 10;

	_vItem.push_back(armor1);

	tagItemInfo armor2;
	armor2.itemKind = ITEM_ARMOR;
	armor2.name = "2. 찬호의 백팩";
	armor2.description = "유사시의 방패로 쓸수있다. (안에 전공책 한가득)";
	armor2.ability = 13;
	armor2.price = 50000;

	_vItem.push_back(armor2);

	tagItemInfo armor3;
	armor3.itemKind = ITEM_ARMOR;
	armor3.name = "3. 덕호의 코트";
	armor3.description = "얼죽코";
	armor3.ability = 87;
	armor3.price = 250;

	_vItem.push_back(armor3);

	tagItemInfo acce1;

	acce1.itemKind = ITEM_ACCESORY;
	acce1.name = "1. 태준이의 회종시계";
	acce1.description = "거래를 하러왔다 도르마무(스위스 산)";
	acce1.ability = 50;
	acce1.price = 30;

	_vItem.push_back(acce1);

	tagItemInfo acce2;
	acce2.itemKind = ITEM_ACCESORY;
	acce2.name = "2. 종환이의 스마트폰";
	acce2.description = "앱등이가 이 악세서리를 싫어합니다";
	acce2.ability = 100;
	acce2.price = 1000;
	
	_vItem.push_back(acce2);

	tagItemInfo acce3;
	acce3.itemKind = ITEM_ACCESORY;
	acce3.name = "3. 현정이의 아이패드";
	acce3.description = "잡스형 세상이 왜 이래";
	acce3.ability = 200;
	acce3.price = 3000;

	_vItem.push_back(acce3);

	tagItemInfo potion1;
	potion1.itemKind = ITEM_POTION;
	potion1.name = "1. 종태의 신발맛 포션";
	potion1.description = "냄새만 견디면 효과는 뛰어나다 효과는!!!";
	potion1.ability = 100;
	potion1.price = 100;
	_vItem.push_back(potion1);

	tagItemInfo potion2;
	potion2.itemKind = ITEM_POTION;
	potion2.name = "2. 현종이의 (지리산) 수";
	potion2.description = "맑고 깨끗해효 (하지만 아리수가 들었다)";
	potion2.ability = 200;
	potion2.price = 200;
	_vItem.push_back(potion2);



}

void shop::itemOutput(int itemNum)
{
	for (_viItem = _vItem.begin(); _viItem != _vItem.end(); ++_viItem)
	{
		if (_viItem->itemKind != itemNum) continue;

		cout << " ======================= 25기 상점 =====================" << endl;
		cout << "이  름 : " << _viItem->name << endl;
		cout << "성  능 : " << _viItem->ability << endl;
		cout << "가  격 : " << _viItem->price << endl;
		cout << "설  명 : " << _viItem->description << endl;
		cout << "========================================================" << endl;
	}
}

