#include "stdafx.h"
#include "soundManager.h"

soundManager::soundManager()
	: _system(nullptr), 
	_channel(nullptr),
	_sound(nullptr)
{	
}

soundManager::~soundManager()
{
}

HRESULT soundManager::init()
{
	//FMOD ���� �ʱ�ȭ
	System_Create(&_system);

	_system->init(TOTALSOUNDBUFFER, FMOD_INIT_NORMAL, NULL);

	_sound = new Sound*[TOTALSOUNDBUFFER];
	_channel = new Channel*[TOTALSOUNDBUFFER];

	_volume = 1.0f;

	memset(_sound, 0, sizeof(Sound*) * TOTALSOUNDBUFFER);
	memset(_channel, 0, sizeof(Channel*) * TOTALSOUNDBUFFER);

	return S_OK;
}

void soundManager::release()
{
	if (_system != nullptr)
	{
		_system->release();
		_system->close();
	}

	delete[] _sound;
	delete[] _channel;
}

void soundManager::update()
{
	_system->update();
}

void soundManager::addSound(string keyName, string soundName, bool bgm, bool loop)
{
	if (loop)
	{
		if (bgm)
		{
			_system->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, NULL, &_sound[_mTotalSounds.size()]);

		}
		else
		{
			_system->createSound(soundName.c_str(), FMOD_LOOP_NORMAL, NULL, &_sound[_mTotalSounds.size()]);
		}
	}
	else
	{
		if (bgm)
		{
			_system->createStream(soundName.c_str(), FMOD_DEFAULT, NULL, &_sound[_mTotalSounds.size()]);

		}
		else
		{
			_system->createSound(soundName.c_str(), FMOD_DEFAULT, NULL, &_sound[_mTotalSounds.size()]);
		}
	}

	_mTotalSounds.insert(make_pair(keyName, &_sound[_mTotalSounds.size()]));
}

void soundManager::play(string keyName, float volume)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//���尡 ��� ����Ϸ��ٺ��ϱ� ��Ű�� �ȳ��Ϳ�!
			_system->playSound(FMOD_CHANNEL_FREE, *iter->second, false, &_channel[count]);

			_channel[count]->setVolume(volume);
			break;
		}
	}
}

void soundManager::stop(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->stop();
			break;
		}
	}
}

void soundManager::pause(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setPaused(true);
			break;
		}
	}
}

void soundManager::resume(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setPaused(false);
			break;
		}
	}
}

void soundManager::setVolume(float volume)
{ // �ϰ������� �º����ϴ� �Լ�..
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		_channel[count]->setVolume(volume);
	}
}

void soundManager::setPoint(string keyName, float portion)
{ // �װ� ã�ƴٰ� ����Ʈ ���ߴ� �Լ�..

	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;
	unsigned int length;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			(*iter->second)->getLength(&length, FMOD_TIMEUNIT_MS);
			_channel[count]->setPosition(length*portion, FMOD_TIMEUNIT_MS);
			break;
		}
	}
}

float soundManager::getPortion(string keyName)
{ // ������� ������� �Լ�
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;
	unsigned int getPos;
	unsigned int length;
	float portion;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->getPosition(&getPos, FMOD_TIMEUNIT_MS);
			(*iter->second)->getLength(&length, FMOD_TIMEUNIT_MS);
			portion = (float)getPos / (float)length;
			break;
		}
	}
	return portion;
}

unsigned int soundManager::getTime(string keyName)
{ // ����ð��������� �Լ�(�и�������)
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;
	unsigned int getPos;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->getPosition(&getPos, FMOD_TIMEUNIT_MS);
			break;
		}
	}
	return getPos;
}


bool soundManager::isPlaySound(string keyName)
{
	bool isPlay;
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->isPlaying(&isPlay);
			break;
		}
	}

	return isPlay;
}

bool soundManager::isPauseSound(string keyName)
{
	bool isPause;
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->getPaused(&isPause);
			break;
		}
	}

	return isPause;
}
