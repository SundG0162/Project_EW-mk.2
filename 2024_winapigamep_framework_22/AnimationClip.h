#pragma once
class Texture;
class Sprite;
class Animator;
class SpriteRenderer;
//#include "Action.h"
class AnimationClip
{
public:
	AnimationClip();
	~AnimationClip();
public:
	void update();
	void render(HDC hdc);
	void release();
public:
	void init(Animator* animator);
	void create(vector<Sprite*>& sprites, float duration);
public:
	void setFrame(int frame) { _currentFrame = frame; }
public:
	//Action<int, int, int> OnAnimationEnd;
private:
	Animator* _animator;
	SpriteRenderer* _spriteRenderer;
	int _currentFrame;
	float _duration;
	float _timer;
	vector<Sprite*> _sprites;
};