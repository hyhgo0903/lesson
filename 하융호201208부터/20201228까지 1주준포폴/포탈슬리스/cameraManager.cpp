#include "stdafx.h"
#include "cameraManager.h"

// ���������� �����ξ��� ī�޶� �Ŵ�������
// y�� ��ũ�� ����� �� ���·� ������


cameraManager::cameraManager()
{
}

cameraManager::~cameraManager()
{
}

HRESULT cameraManager::init()
{
	cameraLocation.x = cameraLocation.y = minimapHeight= minimapWidth= rangeX1 = rangeY1 = 0;
	rangeX2 = MAPSIZEX;	rangeY2 = MAPSIZEY;
	cameraLock = false;

	return S_OK;
}

void cameraManager::release()
{
}

// ī�޶� x(������)
long cameraManager::getCameraX(){return cameraLocation.x;}

// ī�޶� y(������)
long cameraManager::getCameraY(){return cameraLocation.y;}

// (�ʿ�� �� ��) ī�޶� x�� �ٲ���(������)
void cameraManager::setCameraX(long x) { cameraLocation.x = x; }
// (�ʿ�� �� ��) ī�޶� y�� �ٲ���(������)
void cameraManager::setCameraY(long y) { cameraLocation.y = y; }

// focusOnRect(RECT, xȭ���� n����1 �������� �;� ��ũ������, yȭ���� n����1 �������� �;� ��ũ������)
void cameraManager::focusOnRect(RECT & rc, int x)
{
	if (x < 2) x = 2; // �������� ���� �� �־����� �˾Ƽ� 2�� �ٲ���
	// rc�� x������ ī�޶�+(x-1)*��������/x���� ū��� ���������� ī�޶� �̵�
	if ((rc.left + rc.right) / 2 >= cameraLocation.x + WINSIZEX - WINSIZEX / x && !cameraLock)
	{
		if ((rc.left + rc.right) / 2 - (cameraLocation.x + WINSIZEX - WINSIZEX / x) <10) cameraLocation.x = (rc.left + rc.right) / 2 - WINSIZEX + WINSIZEX / x;
		// ������ �ִ°Ÿ� �� �ٿ���
		else cameraLocation.x += 10; // �ָ� �������Ÿ� �������ϰ� �̵�
	}
	if (cameraLocation.x < rangeX1) cameraLocation.x = rangeX1;
	if (cameraLocation.y < rangeY1) cameraLocation.y = rangeY1;
	if (cameraLocation.x > rangeX2 - WINSIZEX) cameraLocation.x = rangeX2 - WINSIZEX;
	if (cameraLocation.y > rangeY2 - WINSIZEY) cameraLocation.y = rangeY2 - WINSIZEY; // ����ó��
}


// �̴ϸ� Ʋ�� �׸��� �Լ� minimap(hdc, ������ x��ǥ, y��ǥ, ��, ����)
void cameraManager::minimap(HDC hdc, int x, int y, int width, int height, bool standardMap)
{
	minimapX = cameraLocation.x + x;
	minimapY = cameraLocation.y + y;
	minimapWidth = width;
	minimapHeight = height;
	Rectangle(hdc, minimapX, minimapY, minimapX + minimapWidth, minimapY + minimapHeight-20);
	minimapRC = { (int)minimapX, (int)minimapY, (int)minimapX + (int)minimapWidth, (int)minimapY + (int)minimapHeight - 20 };
	minimapBaseOnTotalMap = standardMap;
}

// ������ �̴ϸʿ� ������Ʈ�� �߰� minimapObject(hdc, RECT)
int cameraManager::minimapObject(HDC hdc, RECT & rc)
{
	if (minimapHeight == 0 || minimapWidth == 0) return 0; // Ʋ�� �� ��������ٸ� �������
	
	if (rc.left < cameraLocation.x || rc.right > cameraLocation.x + WINSIZEX ||
		rc.top < cameraLocation.y || rc.bottom > cameraLocation.y + WINSIZEY) return 0; // �ʹ� ����� �� �׷���
	//���̴� �� ���̹Ƿ� ���� ����
	Rectangle(hdc, minimapX + (rc.left - cameraLocation.x)*minimapWidth / WINSIZEX,
		minimapY + (rc.top - cameraLocation.y)*minimapHeight / WINSIZEY,
		minimapX + (rc.right - cameraLocation.x)*minimapWidth / WINSIZEX,
		minimapY + (rc.bottom - cameraLocation.y)*minimapHeight / WINSIZEY);
}

// vibrate(�Ը�)
void cameraManager::vibrate(int magnitude)
{
	cameraLocation.x += rand() % (2 * magnitude + 1) - magnitude; // -mag~+mag���� �����ϰ� �̵�
	if (cameraLocation.x < 0) cameraLocation.x = 0;
	if (cameraLocation.x > rangeX2-WINSIZEX) cameraLocation.x = rangeX2 - WINSIZEX;
}
