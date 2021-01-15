#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;
struct tagInvenInfo
{
	int itemKind;			//������ ����
	string name;			//������ �̸�
	string description;		//������ ����
	int ability;			//������ ����
	int price;				//������ ����
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

