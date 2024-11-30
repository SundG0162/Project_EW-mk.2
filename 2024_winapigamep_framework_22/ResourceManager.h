#pragma once
#include "fmod.hpp"
#pragma comment(lib, "fmod_vc")
enum class SOUND_CHANNEL //���帶�� ä��
{
	BGM, EFFECT, END
};
struct SoundInfo
{
	FMOD::Sound* sound; // ���� ���� �޸�
	bool isLoop;		// ���帶�� ������������
};
class Texture;
class ResourceManager
{
	DECLARE_SINGLETON(ResourceManager);
public:
	void init();
	const wchar_t* getResourcePath() const { return _resourcePath; }
public:
	Texture* loadTexture(const wstring& _key, const wstring& _path);
	Texture* findTexture(const wstring& _key);
	void release();
public:
	void loadSound(const wstring& _key, const wstring& _path, bool _isLoop);
	void play(const wstring& _key);
	void stop(SOUND_CHANNEL _channel);
	void volume(SOUND_CHANNEL _channel, float _vol);
	void pause(SOUND_CHANNEL _channel, bool _ispause);
private:
	SoundInfo* findSound(const wstring& _key);
private:
	wchar_t _resourcePath[255] = {};
	map<wstring, Texture*> _textureMap;
	map<wstring, SoundInfo*> _soundMap;
	FMOD::System* _soundSystem; // ���� �ý���
	FMOD::Channel* _channels[(UINT)SOUND_CHANNEL::END]; // ����� ä��
};

