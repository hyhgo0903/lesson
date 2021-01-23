#include "stdafx.h"
#include "playGround.h"
#include <mmsystem.h> //���� ���̺귲�� (�߿�)
#pragma comment(lib, "winmm.lib") //���� ���� (�߿�)

///////////////////////////////�׽�Ʈ
//#include<iostream>
//#pragma comment (linker, "/entry:WinMainCRTStartup /subsystem:console")
using namespace std;
playGround::playGround()
{
}


playGround::~playGround()
{
}

HRESULT playGround::init()
{
	gameNode::init(true);
	addImage();
	SCENEMANAGER->addScene("����ȭ��", new StartScene);
	SCENEMANAGER->addScene("���ν�������", new MainStage);
	SCENEMANAGER->addScene("������������", new BossStage);
	SCENEMANAGER->addScene("�÷��̾��ֱ�", new DeadScene);
	SCENEMANAGER->changeScene("����ȭ��");

	return S_OK;
}


void playGround::release()
{
	gameNode::release();


}

void playGround::update()
{
	gameNode::update();

		SCENEMANAGER->update();
}


void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ ���� �ǵ��� ���� ==============================
	
	SCENEMANAGER->render();
	TIMEMANAGER->render(getMemDC());
	//================= �Ʒ��� �ǵ��� ���� ==============================
	_backBuffer->render(getHDC());
}

void playGround::addImage()
{
	//��
	IMAGEMANAGER->addImage("����ȭ��", "image/StartScene.bmp", 800, 600, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�������", "image/DeadBack.bmp", 800, 600, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�Ǹ�", "image/devil.bmp", 480, 54,8,1, true, RGB(255, 0, 255));
	//�� �̹���
	IMAGEMANAGER->addImage("���", "image/backGround.bmp", 3000, 1200, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���ν�������", "image/map.bmp", 3000, 1200, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�����浹��", "image/picColMap.bmp", 3000, 1200, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("������������", "image/BossStage.bmp", 800, 600, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�����浹��", "image/BossStageCollision.bmp", 800, 600, true, RGB(255, 0, 255));
	//ĳ���� ������ �̹���
	IMAGEMANAGER->addFrameImage("�����Ϲݻ���", "image/ninjaIdle2.bmp", 100, 200, 1,2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�����Ϲݰ���", "image/ninjaAttack2.bmp", 900, 200, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���ɾ���", "image/ninjaSit.bmp", 125, 100, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ɾư���", "image/sitAttack2.bmp", 500, 100,4,2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��������", "image/ninjaJump.bmp", 600, 200,6,2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��ݽ�", "image/normalDash.bmp", 500, 200, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�뽬����", "image/dashAttack.bmp", 500, 200, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�Ϲݽ�", "image/dashLegOnly.bmp", 500, 200, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��������", "image/JumpAttack2.bmp", 600, 200, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���ɺ����", "image/climbUp.bmp", 400, 200, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��������", "image/climbAttack.bmp", 550, 200, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ǰݵ�", "image/ninjaAttacked2.bmp", 100, 200, 1, 2, true, RGB(255, 0, 255));
	//����Ʈ �̹���
	EFFECTMANAGER->addEffect("R����1", "AttackEffect1R.bmp", 340, 30, 85, 30, 2.0f,0.1f,10);
	EFFECTMANAGER->addEffect("R����2", "AttackEffect2R.bmp", 340, 30, 85, 30, 2.0f, 0.1f, 10);
	EFFECTMANAGER->addEffect("L����1", "AttackEffect1L.bmp", 340, 30, 85, 30, 2.0f, 0.1f, 10);
	EFFECTMANAGER->addEffect("L����2", "AttackEffect2L.bmp", 340, 30, 85, 30, 2.0f, 0.1f, 10);
	EFFECTMANAGER->addEffect("��ȭR����1", "ENAttackEffect1R.bmp", 540, 50, 135, 50, 2.0f, 0.1f, 10);
	EFFECTMANAGER->addEffect("��ȭR����2", "ENAttackEffect2R.bmp", 540, 50, 135, 50, 2.0f, 0.1f, 10);
	EFFECTMANAGER->addEffect("��ȭL����1", "ENAttackEffect1L.bmp", 540, 50, 135, 50, 2.0f, 0.1f, 10);
	EFFECTMANAGER->addEffect("��ȭL����2", "ENAttackEffect2L.bmp", 540, 50, 135, 50, 2.0f, 0.1f, 10);

	//���ʹ� �̹���
	IMAGEMANAGER->addFrameImage("����ź�", "image/enemy1GK.bmp", 400, 200, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����", "image/enemy3Worm.bmp", 160, 70, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���Ÿ��ź�", "image/enemy2RK.bmp", 340, 180, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���Ÿ��źϰ���", "image/RKAttack.bmp", 425, 180, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ҵ�������Ʈ", "image/enemyFire.bmp", 32, 52,1,2, true, RGB(255, 0, 255));

	//���� �̹���
	IMAGEMANAGER->addFrameImage("��������", "image/bossAppeal.bmp", 3150, 120, 21, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��������", "image/bossAttack.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�����Ϲ�", "image/bossIdle.bmp", 480, 240, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��������", "image/bossDead.bmp", 1320, 240, 11, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�����̵�", "image/bossMove.bmp", 480, 240, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��������", "image/bossJump.bmp", 360, 240, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�����ǰ�", "image/bossAttacked.bmp", 120, 240, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("������������Ʈ", "image/bossWeapon.bmp", 312, 33, 4,1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��������", "image/BSPattern.bmp", 600, 240, 5, 2, true, RGB(255, 0, 255));

	//UI�� ������ �̹���
	IMAGEMANAGER->addImage("HPUIF", "image/HPStoneFilled.bmp", 12, 28, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("HPUIB", "image/blankHP.bmp", 12, 28, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("MPUIB", "image/blankedMana.bmp", 22, 22, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("MPUIF", "image/ManaStoneFilled.bmp", 22, 22, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("MPR", "image/manaRecover.bmp", 22, 22, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Heal", "image/healing.bmp", 22, 22, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Power", "image/powerCrystal.bmp", 22, 32, true, RGB(255, 0, 255));
}

