#include "stdafx.h"
#include "ItemManager.h"
#include "Messenger.h"
ItemManager::ItemManager()
{
}

ItemManager::~ItemManager()
{
}

HRESULT ItemManager::init()
{

	return S_OK;
}

void ItemManager::release()
{
}

void ItemManager::update(Messenger* mess)
{
	PickupItem(mess);
}

void ItemManager::render(POINT camera)
{
	for (viItem = vItem.begin();viItem != vItem.end();++viItem)
	{
		viItem->img->render(getMemDC(), viItem->rc.left, viItem->rc.top, camera);
	}
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		for (viItem = vItem.begin();viItem != vItem.end();++viItem)
		{
			Rectangle(getMemDC(), viItem->rc,camera);
		}
	}
}
void ItemManager::ItemDrop(int x,int y,int variety)
{
	switch (variety)
	{
	case 0:
		healing(x, y);
		break;
	case 1:
		manaRecover(x, y);
		break;
	case 2:
		PowerStone(x, y);
		break;
	}
}

void ItemManager::healing(int x, int y)
{
	tagItem Item;
	ZeroMemory(&Item, sizeof(tagItem));
	Item.img = IMAGEMANAGER->findImage("Heal");
	Item.rc = RectMakeCenter(x, y, Item.img->getWidth(), Item.img->getHeight());
	Item.type = HEAL;
	vItem.push_back(Item);
	//Item.angle
}

void ItemManager::manaRecover(int x, int y)
{
	tagItem Item;
	ZeroMemory(&Item, sizeof(tagItem));
	Item.img = IMAGEMANAGER->findImage("MPR");
	Item.rc = RectMakeCenter(x, y, Item.img->getWidth(), Item.img->getHeight());
	Item.type = MANA;
	vItem.push_back(Item);

}

void ItemManager::PowerStone(int x, int y)
{
	tagItem Item;
	ZeroMemory(&Item, sizeof(tagItem));
	Item.img = IMAGEMANAGER->findImage("Power");
	Item.rc = RectMakeCenter(x, y, Item.img->getWidth(), Item.img->getHeight());
	Item.type = POWER;
	vItem.push_back(Item);
}

void ItemManager::PickupItem(Messenger* mess)
{
	for (viItem = vItem.begin();viItem != vItem.end();)
	{
		RECT temp;
		if (IntersectRect(&temp, &mess->getMainRC(), &viItem->rc))
		{
			switch (viItem->type)
			{
			case HEAL:
				mess->setHP(1);
				break;
			case MANA:
				mess->setMP(1);
				break;
			case POWER:
				mess->setHP(MAXHP);
				mess->setMP(MAXMP);
				break;
			}
			viItem = vItem.erase(viItem);
		}
		else ++viItem;
	}
}
