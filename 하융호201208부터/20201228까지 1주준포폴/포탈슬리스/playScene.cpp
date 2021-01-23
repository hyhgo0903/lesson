#include "stdafx.h"
#include "playScene.h"

playScene::playScene()
{
}


playScene::~playScene()
{
}

HRESULT playScene::init(int data)
{
	CAMERAMANAGER->setCameraX(0);
	srand(time(NULL));
	_goCount = _goFrameX = _idleTime = 0;
	_wind = 0.f;
	_pm = new playerManager;	_pm->init(data);
	_um = new UIManager;		_um->init();
	_im = new itemManager;		_im->init();
	_bm = new bulletManager;	_bm->init();
	_em = new enemyManager;		_em->init(); // �Ŵ��� Ȥ��
	_pm->setImMemoryAddressLink(_im); // im�� �Լ��� �����۽��� ���� �޾ƿ���. ���� ������ ����. - ��ȣ����
	_pm->setBmMemoryAddressLink(_bm); // bm�� �Լ��� �߻��Ű�� ����(pm�� ���� ���ڸ� �Ű������� �Է�) - ��ȣ����
	_em->setBmMemoryAddressLink(_bm); // bm�� �Լ��� �߻��Ű�� ����(em�� ���� ���ڸ� �Ű������� �Է�) - ��ȣ����
	_em->setImMemoryAddressLink(_im); // im�� �Լ��� ���ʹ��� ��ġ�� ������ ��� �Լ��� ���� ���� - �ܹ��� ����
	_em->setPmMemoryAddressLink(_pm); // pm�� �Լ��� player��ġ�� �����ϰ� �׿����� ���ݹ��� ���� - �ܹ��� ����
	_im->setPmMemoryAddressLink(_pm); // pm�� �Լ��� �÷��̾� rect�� �޾ƿ��� ������ ȹ��(�浹) ó�� - ��ȣ����
	_bm->setPmMemoryAddressLink(_pm); // pm�� �Լ��� rect���� �޾ƿ��� �浹ó�� - ��ȣ����
	_bm->setEmMemoryAddressLink(_em); // em�� �Լ��� rect���� �޾ƿ��� �浹ó�� - ��ȣ����

	return S_OK;
}

HRESULT playScene::init()
{
	CAMERAMANAGER->setCameraX(0);
	srand(time(NULL));
	_goCount = _goFrameX = _idleTime = 0;
	_wind = 0.f;
	_pm = new playerManager;	_pm->init(0);
	_um = new UIManager;		_um->init();
	_im = new itemManager;		_im->init();
	_bm = new bulletManager;	_bm->init();
	_em = new enemyManager;		_em->init(); // �Ŵ��� Ȥ��
	_pm->setImMemoryAddressLink(_im); // im�� �Լ��� �����۽��� ���� �޾ƿ���. ���� ������ ����. - ��ȣ����
	_pm->setBmMemoryAddressLink(_bm); // bm�� �Լ��� �߻��Ű�� ����(pm�� ���� ���ڸ� �Ű������� �Է�) - ��ȣ����
	_em->setBmMemoryAddressLink(_bm); // bm�� �Լ��� �߻��Ű�� ����(em�� ���� ���ڸ� �Ű������� �Է�) - ��ȣ����
	_em->setImMemoryAddressLink(_im); // im�� �Լ��� ���ʹ��� ��ġ�� ������ ��� �Լ��� ���� ���� - �ܹ��� ����
	_em->setPmMemoryAddressLink(_pm); // pm�� �Լ��� player��ġ�� �����ϰ� �׿����� ���ݹ��� ���� - �ܹ��� ����
	_im->setPmMemoryAddressLink(_pm); // pm�� �Լ��� �÷��̾� rect�� �޾ƿ��� ������ ȹ��(�浹) ó�� - ��ȣ����
	_bm->setPmMemoryAddressLink(_pm); // pm�� �Լ��� rect���� �޾ƿ��� �浹ó�� - ��ȣ����
	_bm->setEmMemoryAddressLink(_em); // em�� �Լ��� rect���� �޾ƿ��� �浹ó�� - ��ȣ����

	return S_OK;
}


void playScene::release()
{
	if (_pm) { _pm->release();  SAFE_RELEASE(_pm);	SAFE_DELETE(_pm);}
	if (_um) { _um->release();  SAFE_RELEASE(_um);	SAFE_DELETE(_um); }
	if (_im) { _im->release();  SAFE_RELEASE(_im);	SAFE_DELETE(_im); }
	if (_bm) { _bm->release();  SAFE_RELEASE(_bm);	SAFE_DELETE(_bm); }
	if (_em) { _em->release();  SAFE_RELEASE(_em);	SAFE_DELETE(_em); }
}

void playScene::update()
{
	// _pm, _um ����� nullptr�� �ƴҶ��� �����ϵ���
	if (_pm == nullptr || _um == nullptr || _im == nullptr || _bm == nullptr || _em == nullptr) return;
	if (_pm->getIsGameOver())
	{
		saveRecord();
		SCENEMANAGER->changeScene("���ӿ�����");
		return; // ������ ������� �� ��������..
	}
	if (_em->getIsVictory())
	{
		saveRecord();
		SCENEMANAGER->changeScene("�¸���");
		return;
	}
	if (!(CAMERAMANAGER->getCameraLock()) && _goCount < 6) ++_goCount;
	if (_goCount >= 6)
	{ // �����ϴ°������� �÷��ֱ�
		_goCount = 0;
		++_goFrameX;
		if (_goFrameX >= 16) _goFrameX = 0;
	}
	if (_idleTime < 1000) ++_idleTime;
	else _idleTime = 601; // 1000�̸� 601�� �ٲ��ش�(������ 600���� ũ�⶧���� ������ ������ �Ѵ�)
	if (CAMERAMANAGER->getCameraLock() || _pm->getRect().right >= GETCAM + WINSIZEX / 2 + 23) _idleTime = 0;
	_bm->setWind(_um->getWind());
	_im->setWind(_um->getWind()); // �ٶ����� �������ϰ� �־��ַ��� ���⼭ ��������
	_pm->update();
	_um->update();
	_im->update();
	_bm->update();
	_em->update();
}

void playScene::render()
{
	if (_pm == nullptr || _um == nullptr || _im == nullptr || _bm == nullptr || _em == nullptr) return;
	FINDIMG("��")->render(getMemDC(), GETCAM, 0, GETCAM,0,WINSIZEX,WINSIZEY);
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		FINDIMG("���ȼ�")->render(getMemDC(), GETCAM, 0, GETCAM, 0, WINSIZEX, WINSIZEY);
		TIMEMANAGER->render(getMemDC());
	}
	_um->render();
	_im->render();
	_em->render();
	_pm->render();
	_bm->render();
	interfaceRender();

}



void playScene::saveRecord() // �� �Ѿ���� ����� ���Ϸ� �����ϴ� �Լ�
{	
	char temp[128];	ZeroMemory(temp, sizeof(temp));
	vector<string> vStr;
	
	if (_waccess_s(L"./���.txt", 0) != 0) // ������ ������ 0,0���� �ʱ�ȭ�ؼ� ����
	{ // ������ ������ش�. 0, 0���� �ڵ������.
		vStr.push_back(itoa(0, temp, 10));
		vStr.push_back(itoa(0, temp, 10));
		TXTDATA->txtSave("���.txt", vStr);
	}
	vStr.clear();
	vStr = TXTDATA->txtLoad("���.txt");
	_highScore = atoi(vStr[1].c_str());

	vStr.clear();
	vStr.push_back(itoa(_scoreSum, temp, 10));
	if (_scoreSum > _highScore)	vStr.push_back(itoa(_scoreSum, temp, 10));
	else vStr.push_back(itoa(_highScore, temp, 10));
	TXTDATA->txtSave("���.txt", vStr);
}
