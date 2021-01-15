#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;
struct tagInvenInfo
{
	int itemKind;			//아이템 종류
	string name;			//아이템 이름
	string description;		//아이템 설명
	int ability;			//아이템 성능
	int price;				//아이템 가격
};


class inventory
{
private:
	vector<tagInvenInfo>			_vInven;
	vector<tagInvenInfo>::iterator	_viInven;
public:
	inventory();
	~inventory();
	void inventoryOutput();
	void inventoryOutput(int itemNum);

	void itemBuy(int x);
	void itemSetup2();
	
	tagInvenInfo weapon1;
	tagInvenInfo weapon2;
	tagInvenInfo weapon3;
	tagInvenInfo armor1;
	tagInvenInfo armor2;
	tagInvenInfo armor3;
	tagInvenInfo acce1;
	tagInvenInfo acce2;
	tagInvenInfo acce3;
	tagInvenInfo potion1;
	tagInvenInfo potion2;
};

