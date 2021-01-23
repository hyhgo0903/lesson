#pragma once
#include "singletonBase.h"

class cameraManager : public singletonBase<cameraManager>
{
private:
	POINT cameraLocation;

	bool minimapBaseOnTotalMap;
	// �̴ϸ��� ��ü�ʱ��������ϸ� true, ������â �������� �ϸ� false(minimap�Լ����� ����)

	int vibrationCount;
	int count;


	float rangeX1;	float rangeX2;
	float rangeY1;	float rangeY2;

	bool cameraLock;

	float minimapX;	float minimapY;
	float minimapHeight;
	float minimapWidth;

	RECT minimapRC;

public:
	cameraManager();
	~cameraManager();

	HRESULT init();
	void release();

	// ī�޶� x�� �ҷ��� (������)
	long getCameraX();
	// ī�޶� y�� �ҷ��� (������)
	long getCameraY();

	// (�ʿ�� �� ��) ī�޶� x�� �ٲ���(������)
	void setCameraX(long x);

	// (�ʿ�� �� ��) ī�޶� y�� �ٲ���(������)
	void setCameraY(long y);
	

	// focusOnRect(RECT, xȭ���� n����1 �������� �;� ��ũ������, yȭ���� n����1 �������� �;� ��ũ������)
	void focusOnRect(RECT &rc, int x = 2);
	
	// �̴ϸ� ��ü�� �׸��� �Լ� minimap(hdc, ������ x��ǥ, y��ǥ, ��, ����, ��ü�ʱ������� ���� ���� �ƴϸ� ������â����)
	void minimap(HDC hdc, int x, int y, int width, int height, bool standardMap = false);

	// ������ �̴ϸʿ� ������ ������Ʈ�� �߰� minimapObject(hdc, RECT)
	int minimapObject(HDC hdc, RECT & rc);

	// vibrate(�Ը�) �Ը� ���� ���ص� ��(�⺻��10)
	void vibrate(int magnitude = 10);

	void cameraLockOn() { cameraLock = true; }
	void cameraLockOff() { cameraLock = false; }
	bool getCameraLock() { return cameraLock; }

	RECT getMinimapRC() { return minimapRC; }
};

