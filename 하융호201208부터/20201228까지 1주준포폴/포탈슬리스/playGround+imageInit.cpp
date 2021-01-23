#include "stdafx.h"
#include "playGround.h"

// �ʱ� �̹����߰��� �����ϴ� �Լ��Դϴ�.

void playGround::imageInit()
{
	// �������̽� ���� �̹���
	IMAGEMANAGER->addImage("�������̽�", "image/interface/interface.bmp", 800, 128, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�������̽����׸���", "image/interface/interfaceagain.bmp", 200, 15, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�ʷϹ�", "image/interface/bargreen.bmp", 403, 20, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("������", "image/interface/barred.bmp", 403, 20, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("�Ķ���", "image/interface/barblue.bmp", 403, 20, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("�ٶ�", "image/interface/barwind.bmp", 45, 9, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("��", "image/interface/on.bmp", 59, 25, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����", "image/interface/off.bmp", 56, 23, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��", "image/interface/snow.bmp", 180, 30, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���", "image/interface/firemode.bmp", 29, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("������ũ", "image/interface/currenttank.bmp", 112, 24, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����", "image/interface/number.bmp", 250, 25, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��", "image/interface/go.bmp", 512, 31, 16, 1, true, RGB(255, 0, 255));

	// �� ���� �̹���
	IMAGEMANAGER->addImage("��", "image/map.bmp", 5295, 448, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("���ȼ�", "image/mappixel.bmp", 5295, 448, true, RGB(255, 0, 255));

	// ��ũ ���� �̹���
	IMAGEMANAGER->addFrameImage("ĳ����̵�", "image/tank/cannonidle.bmp", 3120, 236, 39, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ĳ���̵�", "image/tank/cannonrun.bmp", 721, 118, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ĳ�����", "image/tank/cannonattack.bmp", 870, 170, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���ʾ��̵�", "image/tank/missileidle.bmp", 1848, 138, 24, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�����̵�", "image/tank/missilerun.bmp", 584, 154, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���ʰ���", "image/tank/missileattack.bmp", 945, 210, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���ʾ��̵�", "image/tank/multiidle.bmp", 480, 112, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�����̵�", "image/tank/multirun.bmp", 400, 100, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���ʰ���", "image/tank/multiattack.bmp", 663, 154, 13, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���ʾ��̵�", "image/tank/superidle.bmp", 287, 92, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�����̵�", "image/tank/supermove.bmp", 287, 92, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���ʰ���", "image/tank/superattack.bmp", 472, 148, 8, 2, true, RGB(255, 0, 255));

	// ��ũ�� ��ź ���� �̹���
	IMAGEMANAGER->addFrameImage("ĳ���Ϲ�", "image/tankbullet/bulletcannon1.bmp", 92, 23, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ĳ��Ư��", "image/tankbullet/bulletcannon2.bmp", 48, 12, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�����Ϲ�", "image/tankbullet/bulletmissile1.bmp", 216, 27, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����Ư��", "image/tankbullet/bulletmissile2.bmp", 240, 30, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�����Ϲ�", "image/tankbullet/bulletmulti1.bmp", 232, 29, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����Ư��", "image/tankbullet/bulletmulti2.bmp", 144, 18, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�����Ϲ�", "image/tankbullet/bulletsuper1.bmp", 264, 33, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����Ư��", "image/tankbullet/bulletsuper2.bmp", 144, 19, 8, 1, true, RGB(255, 0, 255));

	// ������ ���� �̹���
	IMAGEMANAGER->addImage("���", "image/item/helicopter.bmp", 90, 52, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�����ۻ���", "image/item/box.bmp", 144, 31, 4, 1, true, RGB(255, 0, 255));	// ���������ӷ����Ϸ��� trans true����..
	IMAGEMANAGER->addFrameImage("������", "image/item/stateitem.bmp", 180, 39, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�����۽���", "image/interface/stateitemslot.bmp", 148, 32, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����۽���", "image/interface/usingitemslot.bmp", 124, 31, 4, 1, false, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("����۹���ǥ��", "image/interface/usingitem.bmp", 252, 59, 4, 1, true, RGB(255, 0, 255));

	// �� ���� �̹��� (��� ���ķ��� �� ����)
	IMAGEMANAGER->addFrameImage("��1���", "image/enemy/enemy1idle.bmp", 370, 96, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��1�̵�", "image/enemy/enemy1walk.bmp", 420, 100, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��1����", "image/enemy/enemy1attack.bmp", 1932, 90, 21, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��2���", "image/enemy/enemy2idle.bmp", 116, 76, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��2�̵�", "image/enemy/enemy2walk.bmp", 420, 84, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��2����", "image/enemy/enemy2attack.bmp", 522, 82, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��3", "image/enemy/enemy3.bmp", 752, 40, 16, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��4", "image/enemy/enemy4.bmp", 3912, 121, 24, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��5", "image/enemy/enemy5.bmp", 220, 170, true, RGB(255, 0, 255));

	// �� �Ѿ� ���� �̹���
	IMAGEMANAGER->addFrameImage("���Ѿ�1", "image/enemy/enemybullet1.bmp", 52, 18, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���Ѿ�2", "image/enemy/enemybullet2.bmp", 96, 15, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���Ѿ�3", "image/enemy/enemybullet3.bmp", 26, 26, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���Ѿ�4", "image/enemy/enemybullet4.bmp", 21, 21, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���Ѿ�5", "image/enemy/enemybullet5.bmp", 24, 24, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���Ѿ�6", "image/enemy/enemybullet6.bmp", 24, 24, true, RGB(255, 0, 255));

	// ����Ʈ ���� �̹���
	IMAGEMANAGER->addFrameImage("�ٶ�����Ʈ", "image/effectwind.bmp", 276, 75, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("������Ʈ", "image/effectpower.bmp", 320, 65, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��������Ʈ", "image/effectshield.bmp", 455, 92, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("������Ʈ", "image/effectheal.bmp", 675, 50, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Ÿ��", "image/target.bmp", 80, 80, true, RGB(255, 0, 255));
	// ���⼭���ʹ� ����Ʈ�Ŵ����� ������ ����Ʈ(�ܹ߼�)
	IMAGEMANAGER->addImage("��ü", "image/effectchange.bmp", 800, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���ǵ��", "image/effectspeedup.bmp", 900, 29, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�Ŀ���", "image/effectpowerup.bmp", 980, 29, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�����̴ٿ�", "image/effectdelaydown.bmp", 900, 29, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���ھ��", "image/effectscore.bmp", 900, 29, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����", "image/explosion.bmp", 832, 62, true, RGB(255, 0, 255));

	// �� ���� �̹���
	IMAGEMANAGER->addImage("���ξ�", "image/scene/main.bmp", 800, 527, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("����Ʈ��", "image/scene/select.bmp", 800, 527, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("�Ŵ���", "image/scene/manual.bmp", 800, 527, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("���ӿ�����", "image/scene/gameover.bmp", 800, 527, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("�¸���", "image/scene/victory.bmp", 800, 527, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("��ũ���ùڽ�", "image/scene/selecttabletank.bmp", 247, 109, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���̵����ùڽ�", "image/scene/selecttabledifficulty.bmp", 264, 138, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�ʱ⼱�ùڽ�", "image/scene/selecttable.bmp", 218, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��ϰ���", "image/scene/record.bmp", 120, 116, true, RGB(255, 0, 255));
	
}
