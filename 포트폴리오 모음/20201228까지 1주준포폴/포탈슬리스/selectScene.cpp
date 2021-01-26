#include "stdafx.h"
#include "selectScene.h"

selectScene::selectScene()
{
}

selectScene::~selectScene()
{
}


HRESULT selectScene::init()
{
	CAMERAMANAGER->setCameraX(0);
	_manualPop = _selectPhase = _selected = false;
	_data = 0;
	_cursor[0] = 0; _cursor[1] = -1;
	return S_OK;
}

void selectScene::release()
{
}

void selectScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN) && !_manualPop && !_selectPhase && _cursor[0] < 2)
	{	++_cursor[0];	} // ����������� �Ʒ���ư�� ������		
	if (KEYMANAGER->isOnceKeyDown(VK_UP) && !_manualPop && !_selectPhase && _cursor[0] > 0)
	{	--_cursor[0];	} // ����������� ����ư ������
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT) && _selectPhase)
	{ // ����Ʈ ������� �¿�
		if (!_selected && _cursor[0] < 2) ++_cursor[0];
		if (_selected && _cursor[1] < 2) ++_cursor[1];
	} // ����Ʈ ������� ������ ��ư�� ������		
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT) && _selectPhase)
	{
		if (!_selected && _cursor[0] > 0) --_cursor[0];
		if (_selected && _cursor[1] > 0) --_cursor[1];
	} // ����Ʈ ����������� ���ʹ�ư ������
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		if (!_manualPop && !_selectPhase && _cursor[0] == 0) _selectPhase = true;
		//�����������
		else if (!_manualPop && !_selectPhase && _cursor[0] == 1) _manualPop = true;
		// �Ŵ���Ű��
		else if (_manualPop) _manualPop = false; // �Ŵ��� ����
		else if (!_manualPop && !_selectPhase && _cursor[0] == 2) PostQuitMessage(0); // ����
		else if (_selectPhase && _cursor[0]==0 && !_selected) // ���̵� ����
		{_selected = true;	_data = 0; _cursor[1] = 0;}
		else if (_selectPhase && _cursor[0] == 1 && !_selected)
		{_selected = true;	_data = 10; _cursor[1] = 0;}
		else if (_selectPhase && _cursor[0] == 2 && !_selected)
		{_selected = true;	_data = 20; _cursor[1] = 0;}
		else if (_selectPhase && _cursor[1] == 0 && _selected) // �ʱ� ��ũ�����ϰ�
		{
			SCENEMANAGER->changeScene("�÷��̾�", _data);
		} // �����ϰ� ��ü��������
		else if (_selectPhase && _cursor[1] == 1 && _selected)
		{
			SCENEMANAGER->changeScene("�÷��̾�", _data + 1);
		}
		else if (_selectPhase && _cursor[1] == 2 && _selected)
		{
			SCENEMANAGER->changeScene("�÷��̾�", _data+2);
		}
	}


}

void selectScene::render()
{
	if (!_selectPhase)
	{
		FINDIMG("���ξ�")->render(getMemDC());
		switch (_cursor[0])
		{
		case 0: FINDIMG("�ʱ⼱�ùڽ�")->render(getMemDC(), 575, 186);	break;
		case 1: FINDIMG("�ʱ⼱�ùڽ�")->render(getMemDC(), 575, 275);	break;
		case 2: FINDIMG("�ʱ⼱�ùڽ�")->render(getMemDC(), 575, 364);	break;
		}
	}
	if (_manualPop)	FINDIMG("�Ŵ���")->render(getMemDC());
	if (_selectPhase)
	{
		FINDIMG("����Ʈ��")->render(getMemDC());
		switch (_cursor[0])
		{
		case 0:FINDIMG("���̵����ùڽ�")->render(getMemDC(), 8, 80);	break;
		case 1:FINDIMG("���̵����ùڽ�")->render(getMemDC(), 275, 80);	break;
		case 2:FINDIMG("���̵����ùڽ�")->render(getMemDC(), 535, 80);	break;
		}
		switch (_cursor[1])
		{
		case -1:break;
		case 0:FINDIMG("��ũ���ùڽ�")->render(getMemDC(), 7, 336);	break;
		case 1:FINDIMG("��ũ���ùڽ�")->render(getMemDC(), 280, 336);	break;
		case 2:FINDIMG("��ũ���ùڽ�")->render(getMemDC(), 547, 336);	break;
		}
	}
}