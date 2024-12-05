#include "pch.h"
#include "ResourceManager.h"
#include "Core.h"
#include "Texture.h"
#include "Sprite.h"
void ResourceManager::init()
{
	::GetCurrentDirectory(255, _resourcePath);
	wcscat_s(_resourcePath, 255, L"\\Resource\\");
	//::SetWindowText(GET_SINGLE(Core)->GetHwnd(), m_resourcePath);

	FMOD::System_Create(&_soundSystem); // �ý��� ���� �Լ�
	if (_soundSystem != nullptr)
		_soundSystem->init((int)SOUND_CHANNEL::END, FMOD_INIT_NORMAL, nullptr);

	loadTexture(L"Test", L"Texture\\Test.bmp");
	loadTexture(L"Title-1", L"Texture\\title-1.bmp");
	loadTexture(L"Title-2", L"Texture\\title-2.bmp");
	loadTexture(L"Title-3", L"Texture\\title-3.bmp");
	loadTexture(L"Title-4", L"Texture\\title-4.bmp");
	loadTexture(L"Computer", L"Texture\\Computer.bmp");
	loadTexture(L"Camera", L"Texture\\CameraScreen.bmp");
	loadTexture(L"BarUI", L"Texture\\BarUI.bmp");
	loadTexture(L"Torch", L"Texture\\Torch.bmp");
	loadTexture(L"BasicEnemy", L"Texture\\BasicEnemy.bmp");
	loadTexture(L"UpgradeCard", L"Texture\\UpgradeCard.bmp");
	loadTexture(L"PowerIcon", L"Texture\\PowerIcon.bmp");
	loadTexture(L"CameraIcon", L"Texture\\CameraIcon.bmp");
	loadTexture(L"CCTVIcon", L"Texture\\CCTVIcon.bmp");
	loadTexture(L"BasicEnemy", L"Texture\\BasicEnemy.bmp");
	loadTexture(L"ExplodeEffect", L"Texture\\ExplodeEffect.bmp");
	loadTexture(L"Dinosaur", L"Texture\\Dinosaur.bmp");
	loadTexture(L"Dinosaur", L"Texture\\Dinosaur.bmp");
	loadTexture(L"ForderEnemyTransition", L"Texture\\ForderEnemyTransition.bmp");
	loadTexture(L"ForderEnemyIdle", L"Texture\\ForderEnemyIdle.bmp");
	loadTexture(L"EnemySheet", L"Texture\\EnemySheet.bmp");

	for (auto pair : _textureMap)
	{
		Texture* texture = pair.second;
		loadSprite(pair.first, utils::SpriteParser::textureToSprite(texture));
	}
}

Texture* ResourceManager::loadTexture(const wstring& _key, const wstring& _path)
{
	Texture* texture = getTexture(_key);
	if (nullptr != texture)
		return texture;

	// ����� �����Դϴ�. ������ּ���.
	// 1. ��� ����
	wstring texpath = _resourcePath;
	texpath += _path;

	// 2. Texture ��������?
	texture = new Texture;
	texture->loadBmp(texpath);
	_textureMap.insert({ _key,texture });
	return texture;
}

Texture* ResourceManager::getTexture(const wstring& _key)
{
	auto iter = _textureMap.find(_key);
	if (iter != _textureMap.end())
		return iter->second;
	return nullptr;
}

Sprite* ResourceManager::loadSprite(const wstring& key, Sprite* sprite)
{
	Sprite* spr = getSprite(key);
	if (spr)
		return spr;
	_spriteMap.insert({ key,sprite });
	return sprite;
}

Sprite* ResourceManager::getSprite(const wstring& key)
{
	auto iter = _spriteMap.find(key);
	if (iter != _spriteMap.end())
		return iter->second;
	return nullptr;
}

void ResourceManager::release()
{
	{
		map<wstring, Texture*>::iterator iter;
		for (iter = _textureMap.begin(); iter != _textureMap.end(); ++iter)
			delete iter->second;
		_textureMap.clear();
	}
	{
		map<wstring, Sprite*>::iterator iter;
		for (iter = _spriteMap.begin(); iter != _spriteMap.end(); ++iter)
			delete iter->second;
		_spriteMap.clear();
	}
	{
		map<wstring, SoundInfo*>::iterator iter;
		for (iter = _soundMap.begin(); iter != _soundMap.end(); ++iter)
		{
			if (nullptr != iter->second)
				delete iter->second;
		}
		_soundMap.clear();
	}
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
