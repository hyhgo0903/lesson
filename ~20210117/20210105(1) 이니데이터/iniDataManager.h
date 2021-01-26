#pragma once
#include "singletonBase.h"
#include <vector>

//대항의시대2 db관리, 어떤 대사를 쳐야하는지 등등..

using namespace std;

struct tagIniData
{
	const char* subject;	//항목   여포
	const char* title;		//제목   무력
	const char* body;		//값     100
};

class iniDataManager : public singletonBase<iniDataManager>
{
private:
	typedef vector<tagIniData>				arrIniData; // tag는 여포 무력 100 으로 묶는거
	typedef vector<tagIniData>::iterator	arrIniDataIter;

	typedef vector<arrIniData>				arrIniDatas; // arr는 장수 군사..로 묶는거(벡터를 담는 벡터)
	typedef vector<arrIniData>::iterator	arrIniDatasIter;

private:
	arrIniDatas _vIniData;


public:
	iniDataManager();
	~iniDataManager();

	HRESULT init();
	
	//데이터 추가 함수
	void addData(const char* subject, const char* title, const char* body);
	//ini파일 만들어주는 함수
	void iniSave(const char* fileName);

	//문자열 데이터 불러오는 함수
	string loadDataString(const char* fileName, const char* subject, const char* title);

	//정수 데이터 불러오는 함수
	int loadDataInterger(const char* fileName, const char* subject, const char* title);

};

