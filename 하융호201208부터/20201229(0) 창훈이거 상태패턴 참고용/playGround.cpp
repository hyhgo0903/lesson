#include "stdafx.h"
#include "playGround.h"
#include <mmsystem.h> //음악 라이브럴리 (중요)
#pragma comment(lib, "winmm.lib") //음악 관련 (중요)

///////////////////////////////테스트
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
	SCENEMANAGER->addScene("시작화면", new StartScene);
	SCENEMANAGER->addScene("메인스테이지", new MainStage);
	SCENEMANAGER->addScene("보스스테이지", new BossStage);
	SCENEMANAGER->addScene("플레이어주금", new DeadScene);
	SCENEMANAGER->changeScene("시작화면");

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
	//================ 위에 건들지 마라 ==============================
	
	SCENEMANAGER->render();
	TIMEMANAGER->render(getMemDC());
	//================= 아래도 건들지 마라 ==============================
	_backBuffer->render(getHDC());
}

void playGround::addImage()
{
	//씬
	IMAGEMANAGER->addImage("시작화면", "image/StartScene.bmp", 800, 600, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("죽음배경", "image/DeadBack.bmp", 800, 600, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("악마", "image/devil.bmp", 480, 54,8,1, true, RGB(255, 0, 255));
	//맵 이미지
	IMAGEMANAGER->addImage("배경", "image/backGround.bmp", 3000, 1200, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("메인스테이지", "image/map.bmp", 3000, 1200, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("메인충돌용", "image/picColMap.bmp", 3000, 1200, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("보스스테이지", "image/BossStage.bmp", 800, 600, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("보스충돌용", "image/BossStageCollision.bmp", 800, 600, true, RGB(255, 0, 255));
	//캐릭터 프레임 이미지
	IMAGEMANAGER->addFrameImage("전령일반상태", "image/ninjaIdle2.bmp", 100, 200, 1,2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("전령일반공격", "image/ninjaAttack2.bmp", 900, 200, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("전령앉음", "image/ninjaSit.bmp", 125, 100, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("앉아공격", "image/sitAttack2.bmp", 500, 100,4,2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("전령점프", "image/ninjaJump.bmp", 600, 200,6,2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("상반신", "image/normalDash.bmp", 500, 200, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("대쉬공격", "image/dashAttack.bmp", 500, 200, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("하반신", "image/dashLegOnly.bmp", 500, 200, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("점프공격", "image/JumpAttack2.bmp", 600, 200, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("전령붙잡기", "image/climbUp.bmp", 400, 200, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("붙잡고공격", "image/climbAttack.bmp", 550, 200, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("피격됨", "image/ninjaAttacked2.bmp", 100, 200, 1, 2, true, RGB(255, 0, 255));
	//이펙트 이미지
	EFFECTMANAGER->addEffect("R공격1", "AttackEffect1R.bmp", 340, 30, 85, 30, 2.0f,0.1f,10);
	EFFECTMANAGER->addEffect("R공격2", "AttackEffect2R.bmp", 340, 30, 85, 30, 2.0f, 0.1f, 10);
	EFFECTMANAGER->addEffect("L공격1", "AttackEffect1L.bmp", 340, 30, 85, 30, 2.0f, 0.1f, 10);
	EFFECTMANAGER->addEffect("L공격2", "AttackEffect2L.bmp", 340, 30, 85, 30, 2.0f, 0.1f, 10);
	EFFECTMANAGER->addEffect("강화R공격1", "ENAttackEffect1R.bmp", 540, 50, 135, 50, 2.0f, 0.1f, 10);
	EFFECTMANAGER->addEffect("강화R공격2", "ENAttackEffect2R.bmp", 540, 50, 135, 50, 2.0f, 0.1f, 10);
	EFFECTMANAGER->addEffect("강화L공격1", "ENAttackEffect1L.bmp", 540, 50, 135, 50, 2.0f, 0.1f, 10);
	EFFECTMANAGER->addEffect("강화L공격2", "ENAttackEffect2L.bmp", 540, 50, 135, 50, 2.0f, 0.1f, 10);

	//에너미 이미지
	IMAGEMANAGER->addFrameImage("녹색거북", "image/enemy1GK.bmp", 400, 200, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("벌레", "image/enemy3Worm.bmp", 160, 70, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("원거리거북", "image/enemy2RK.bmp", 340, 180, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("원거리거북공격", "image/RKAttack.bmp", 425, 180, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("불덩이이펙트", "image/enemyFire.bmp", 32, 52,1,2, true, RGB(255, 0, 255));

	//보스 이미지
	IMAGEMANAGER->addFrameImage("보스등장", "image/bossAppeal.bmp", 3150, 120, 21, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("보스공격", "image/bossAttack.bmp", 720, 240, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("보스일반", "image/bossIdle.bmp", 480, 240, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("보스죽음", "image/bossDead.bmp", 1320, 240, 11, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("보스이동", "image/bossMove.bmp", 480, 240, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("보스점프", "image/bossJump.bmp", 360, 240, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("보스피격", "image/bossAttacked.bmp", 120, 240, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("보스공격이펙트", "image/bossWeapon.bmp", 312, 33, 4,1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("보스패턴", "image/BSPattern.bmp", 600, 240, 5, 2, true, RGB(255, 0, 255));

	//UI와 아이템 이미지
	IMAGEMANAGER->addImage("HPUIF", "image/HPStoneFilled.bmp", 12, 28, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("HPUIB", "image/blankHP.bmp", 12, 28, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("MPUIB", "image/blankedMana.bmp", 22, 22, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("MPUIF", "image/ManaStoneFilled.bmp", 22, 22, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("MPR", "image/manaRecover.bmp", 22, 22, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Heal", "image/healing.bmp", 22, 22, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Power", "image/powerCrystal.bmp", 22, 32, true, RGB(255, 0, 255));
}

