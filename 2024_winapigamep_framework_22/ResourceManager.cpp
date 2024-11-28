#include "pch.h"
#include "ResourceManager.h"
#include "Core.h"
#include "Texture.h"
void ResourceManager::init()
{
	::GetCurrentDirectory(255, _resourcePath);
	wcscat_s(_resourcePath, 255, L"\\Resource\\");
	//::SetWindowText(GET_SINGLE(Core)->GetHwnd(), m_resourcePath);

 	FMOD::System_Create(&_soundSystem); // �ý��� ���� �Լ�
	if (_soundSystem != nullptr)
		_soundSystem->init((int)SOUND_CHANNEL::END, FMOD_INIT_NORMAL, nullptr);

	textureLoad(L"Test", L"Texture\\Test.bmp");
	textureLoad(L"Title-1", L"Texture\\title-1.bmp");
	textureLoad(L"Title-2", L"Texture\\title-2.bmp");
	textureLoad(L"Title-3", L"Texture\\title-3.bmp");
	textureLoad(L"Title-4", L"Texture\\title-4.bmp");
	textureLoad(L"Computer", L"Texture\\Computer.bmp");
	textureLoad(L"Camera", L"Texture\\CameraScreen.bmp");
}

Texture* ResourceManager::textureLoad(const wstring& _key, const wstring& _path)
{
	Texture* texture = textureFind(_key);
	if (nullptr != texture)
		return texture;

	// ����� �����Դϴ�. ������ּ���.
	// 1. ��� ����
	wstring texpath = _resourcePath;
	texpath += _path;
	
	// 2. Texture ��������?
	texture = new Texture;
	texture->loadBmp(texpath);
	_textureMap.insert({_key,texture});
	return texture;
}

Texture* ResourceManager::textureFind(const wstring& _key)
{
	auto iter = _textureMap.find(_key);
	if (iter != _textureMap.end())
		return iter->second;
	return nullptr;
}

void ResourceManager::release()
{
	map<wstring, Texture*>::iterator iter;
	for (iter = _textureMap.begin(); iter != _textureMap.end(); ++iter)
		delete iter->second;
	_textureMap.clear();

	// SOUND
	map<wstring, SoundInfo*>::iterator itersod;
	for (itersod = _soundMap.begin(); itersod != _soundMap.end(); ++itersod)
	{
		if (nullptr != itersod->second)
			delete itersod->second;
	}
	_soundMap.clear();

	// �� ���� �� �� �ý��� �ݰ� ��ȯ
	_soundSystem->close();
	_soundSystem->release();
}

void ResourceManager::loadSound(const wstring& _key, const wstring& _path, bool _isLoop)
{
	if (findSound(_key))
		return;
	wstring strFilePath = _resourcePath;
	strFilePath += _path;
	std::string str;
	str.assign(strFilePath.begin(), strFilePath.end());
	FMOD_MODE eMode = FMOD_LOOP_NORMAL;
	if (!_isLoop)
		eMode = FMOD_DEFAULT;

	SoundInfo* ptSound = new SoundInfo;
	ptSound->isLoop = _isLoop;
	_soundSystem->createSound(str.c_str(), eMode, nullptr, &ptSound->sound);
	_soundMap.insert({ _key, ptSound });
}

void ResourceManager::play(const wstring& _key)
{
	SoundInfo* ptSound = findSound(_key);
	if (!ptSound)
		return;
	_soundSystem->update();
	SOUND_CHANNEL eChannel = SOUND_CHANNEL::BGM;
	if (!ptSound->isLoop)
		eChannel = SOUND_CHANNEL::EFFECT;
	// ���� ��� �Լ�. &channel�� � ä���� ���� ����Ǵ��� ������ �ѱ�
	_soundSystem->playSound(ptSound->sound, nullptr, false, &_channels[(UINT)eChannel]);
}

void ResourceManager::stop(SOUND_CHANNEL _channel)
{
	_channels[(UINT)_channel]->stop();
}

void ResourceManager::volume(SOUND_CHANNEL _channel, float _vol)
{
	// 0.0 ~ 1.0 ���� ����
	_channels[(UINT)_channel]->setVolume(_vol);
}

void ResourceManager::pause(SOUND_CHANNEL _channel, bool _ispause)
{
	// bool���� true�� �Ͻ�����. ��, �� �Լ��� ������ Createsound�Ҷ� 
// FMOD_MODE�� FMOD_LOOP_NORMAL �̾�� ��.
	_channels[(UINT)_channel]->setPaused(_ispause);
}

SoundInfo* ResourceManager::findSound(const wstring& _key)
{
	map<wstring, SoundInfo*>::iterator iter = _soundMap.find(_key);

	if (iter == _soundMap.end())
		return nullptr;
	return iter->second;
}
