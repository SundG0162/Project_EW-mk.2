#pragma once
class Texture;
class Sprite;
class Animator;
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
	void create(vector<Sprite*>& sprites, float duration);
public:
	void setFrame(int frame) { _currentFrame = frame; }
	void setAnimator(Animator* animator) { _animator = animator; }
public:
	//Action<int, int, int> OnAnimationEnd;
private:
	Animator* _animator;
	int _currentFrame;
	float _duration;
	float _timer;
	vector<Sprite*> _sprites;
};