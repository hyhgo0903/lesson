#pragma once
//SingletonBase
//싱글톤화하면 이미지 초기화같은거 없이
//호출만 하면 불러올 수 있음

// 클래스 템플릿
template <typename T>
class singletonBase
{
protected:
	static T* singleton;

	singletonBase() {}
	~singletonBase() {}
public:
	static T* getSingleton();
	void releaseSingleton();
};

template<typename T>
T* singletonBase<T>::singleton = 0;

template<typename T>
inline T* singletonBase<T>::getSingleton()
{
	if (!singleton) singleton = new T;
	// 싱글톤이 없으면 새로 만듦
	return singleton;
}

template<typename T>
inline void singletonBase<T>::releaseSingleton()
{
	if (singleton) // 싱글톤이 있으면
	{
		delete singleton; // 지우고 널값넣어줌
		singleton = nullptr;
	}
}
