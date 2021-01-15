#pragma once
class image
{
public:

	enum IMAGE_LOAD_KIND // �̹��� �ҷ����� ����
	{
		LOAD_RESOURCE,	//���ҽ� ���Ϸκ���
		LOAD_FILE,		//�̹��� ���Ϸκ���
		LOAD_EMPTY,		//�� ��Ʈ�� �̹����� ������� �ְ�
		LOAD_END		//�ʱ�ȭ�� ���ؼ�
	};

	typedef struct tagImageInfo
	{
		DWORD resID;	//���ҽ��� �ҷ��ö� ����� ID��
		HDC hMemDC;
		HBITMAP hBit;
		HBITMAP hOBit;
		int width;
		int height;
		BYTE loadType;	//�̹��� �ҷ��� Ÿ��

		tagImageInfo()
		{
			resID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			width = 0;
			height = 0;
			loadType = LOAD_RESOURCE;
		}

	}IMAGE_INFO, *LPIMAGE_INFO;

private:
	LPIMAGE_INFO	_imageInfo;	
	CHAR*			_fileName;		//���� �̸�
	BOOL			_trans;			//Ư�� �ȼ����� �������� ����
	COLORREF		_transColor;	//������ �ȼ���
public:

	image();
	~image();

	HRESULT init(int width, int height);
	HRESULT init(const char* fileName, int width, int height,
		BOOL trans = FALSE, COLORREF transColor = FALSE);
	void release();
	void setTransColor(BOOL trans, COLORREF transColor);
	void render(HDC hdc, int destX, int destY);

	inline HDC getMemDC() { return _imageInfo->hMemDC; }
};

