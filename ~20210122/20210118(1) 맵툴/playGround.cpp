#include "stdafx.h"
#include "playGround.h"

//��Ʈ������ ����Ʈ������(�ڵ��ϼ�)
//��Ʈ�����ڷ� ����ϰ� ���� (����)?
//OPENFILENAME = Ž����ó�� ��γ�Ÿ����

playGround::playGround()
{
}


playGround::~playGround()
{
}

HRESULT playGround::init()
{
	gameNode::init(true);

	IMAGEMANAGER->addFrameImage("mapTiles", "maptiles.bmp", 0, 0, 640, 288, SAMPLETILEX, SAMPLETILEY, true, RGB(255, 0, 255));

	setup();

	
	return S_OK;
}


void playGround::release()
{
	gameNode::release();

	
}

void playGround::update()
{
	gameNode::update();

	
}


void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ ���� �ǵ��� ���� ==============================
	
	IMAGEMANAGER->render("mapTiles", getMemDC(), WINSIZEX - IMAGEMANAGER->findImage("mapTiles")->getWidth(), 0);

	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		IMAGEMANAGER->findImage("mapTiles")->frameRender(getMemDC(),
			_tiles[i].rc.left, _tiles[i].rc.top,
			_tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
	}

	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		//������Ʈ �Ӽ��� NONE�̸� �������� �׸�������(continue)
		if (_tiles[i].obj == OBJ_NONE) continue;

		IMAGEMANAGER->findImage("mapTiles")->frameRender(getMemDC(),
			_tiles[i].rc.left, _tiles[i].rc.top,
			_tiles[i].objFrameX, _tiles[i].objFrameY);
	}



	//TIMEMANAGER->render(getMemDC());
	//================= �Ʒ��� �ǵ��� ���� ==============================
	_backBuffer->render(getHDC());
}

void playGround::setup()
{
	//ws_child �ڽ�������	HMENU(0)�ν��Ͻ���ȣ ���ӳ�忡 enum CTRL ����.
	   
	_btnSave = CreateWindow("button", "Save", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 700, 500, 100, 30, _hWnd, HMENU(0), _hInstance, NULL);
	_btnLoad = CreateWindow("button", "Load", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 800, 500, 100, 30, _hWnd, HMENU(1), _hInstance, NULL);
	_btnTerrainDraw = CreateWindow("button", "����", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 700, 560, 100, 30, _hWnd, HMENU(2), _hInstance, NULL);
	_btnObjectDraw = CreateWindow("button", "������Ʈ", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 800, 560, 100, 30, _hWnd, HMENU(3), _hInstance, NULL);
	_btnEraser = CreateWindow("button", "���찳", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 900, 560, 100, 30, _hWnd, HMENU(4), _hInstance, NULL);
	_twoByTwo = CreateWindow("button", "2X2", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 1000, 560, 100, 30, _hWnd, HMENU(5), _hInstance, NULL);
	_fourByFour = CreateWindow("button", "4X4", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 1100, 560, 100, 30, _hWnd, HMENU(6), _hInstance, NULL);
	_crtlZ = CreateWindow("button", "�������", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 900, 500, 100, 30, _hWnd, HMENU(7), _hInstance, NULL);

	_crtSelect = CTRL_TERRAINDRAW;

	for (int i = 0; i < SAMPLETILEY; ++i)
	{
		for (int j = 0; j < SAMPLETILEX; ++j)
		{
			_sampleTile[i * SAMPLETILEX + j].terrainFrameX = j;
			_sampleTile[i * SAMPLETILEX + j].terrainFrameY = i;
			
			//RectMake, RectMakeCenter
			//setRect: ��Ʈ ��� �Լ�(����)

			/*SetRect(&_sampleTile[i * SAMPLETILEX + j].rcTile,
				(WINSIZEX - IMAGEMANAGER->findImage("mapTiles")->getWidth()) + j * TILESIZE,
				i * TILESIZE,
				(WINSIZEX - IMAGEMANAGER->findImage("mapTiles")->getWidth()) + j * TILESIZE + TILESIZE,
				i * TILESIZE + TILESIZE);*/

			_sampleTile[i * SAMPLETILEX + j].rcTile = {
				(WINSIZEX - IMAGEMANAGER->findImage("mapTiles")->getWidth()) + j * TILESIZE,
				i * TILESIZE,
				(WINSIZEX - IMAGEMANAGER->findImage("mapTiles")->getWidth()) + j * TILESIZE + TILESIZE,
				i * TILESIZE + TILESIZE };
		}
	}

	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			SetRect(&_tiles[i * TILEX + j].rc,
				j * TILESIZE,
				i * TILESIZE,
				j * TILESIZE + TILESIZE,
				i * TILESIZE + TILESIZE);
		}
	}

	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		_tiles[i].terrainFrameX = 3;
		_tiles[i].terrainFrameY = 0;
		_tiles[i].objFrameX = 0;
		_tiles[i].objFrameY = 0;
		_tiles[i].terrain = terrainSelect(_tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
		_tiles[i].obj = OBJ_NONE;
	}
}

void playGround::setMap()
{
	//������ ���϶��̶�
	for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; ++i)
	{
		if (PtInRect(&_sampleTile[i].rcTile, _ptMouse))
		{
			_currentTile.x = _sampleTile[i].terrainFrameX;
			_currentTile.y = _sampleTile[i].terrainFrameY;
			break;
		}
	}

	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		if (PtInRect(&_tiles[i].rc, _ptMouse))
		{
			if (_crtSelect == CTRL_TERRAINDRAW)
			{
				_tiles[i].terrainFrameX = _currentTile.x;
				_tiles[i].terrainFrameY = _currentTile.y;

				_tiles[i].terrain = terrainSelect(_currentTile.x, _currentTile.y);
			}
			else if (_crtSelect == CTRL_OBJDRAW)
			{
				_tiles[i].objFrameX = _currentTile.x;
				_tiles[i].objFrameY = _currentTile.y;

				_tiles[i].obj = objSelect(_currentTile.x, _currentTile.y);
			}
			else if (_crtSelect == CTRL_ERASER)
			{
				_tiles[i].objFrameX = NULL;
				_tiles[i].objFrameY = NULL;
				_tiles[i].obj = OBJ_NONE;
			}

			InvalidateRect(_hWnd, NULL, false);
			break;
		}
	}

}

void playGround::save()
{
	HANDLE file;
	DWORD write;

	file = CreateFile("saveMap1.map", GENERIC_WRITE, NULL, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &write, NULL);

	CloseHandle(file);

}

void playGround::load()
{
	HANDLE file;
	DWORD read;

	file = CreateFile("saveMap1.map", GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);

	CloseHandle(file);
}

void playGround::tempSave()
{
	if (_ptMouse.x > 640 || _ptMouse.y > 640) return;
	HANDLE file;
	DWORD write;

	file = CreateFile("temp.map", GENERIC_WRITE, NULL, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &write, NULL);

	CloseHandle(file);
}

void playGround::tempLoad()
{
	HANDLE file;
	DWORD read;

	file = CreateFile("temp.map", GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);

	CloseHandle(file);
}

TERRAIN playGround::terrainSelect(int frameX, int frameY)
{
	if (frameX == 1 && frameY == 0) return TR_CEMENT;
	if (frameX == 2 && frameY == 0) return TR_DESERT;
	if (frameX == 3 && frameY == 0) return TR_GRASS;
	if (frameX == 4 && frameY == 0) return TR_WATER;

	//�⺻��.. �ܵ�δٰ�
	return TR_GRASS;
}

OBJECT playGround::objSelect(int frameX, int frameY)
{
	if (frameX == 0 && frameY == 0) return OBJ_TANK1;
	if (frameX == 0 && frameY == 9) return OBJ_TANK2;
	if (frameX == 3 && frameY == 3) return OBJ_BLOCK1;
	if (frameX == 4 && frameY == 4) return OBJ_BLOCK3;
	if (frameX == 15 && frameY == 3) return OBJ_BLOCKS;

	return OBJ_BLOCK1;
}

