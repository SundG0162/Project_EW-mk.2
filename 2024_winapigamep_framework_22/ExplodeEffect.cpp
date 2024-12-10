#include "pch.h"
#include "ExplodeEffect.h"
#include "AnimationClip.h"
#include "ResourceManager.h"

ExplodeEffect::ExplodeEffect()
{
	AnimationClip* clip = new AnimationClip();
	Texture* tex = GET_SINGLETON(ResourceManager)->getTexture(L"ExplodeEffect");
	vector<Sprite*> sprites = utils::SpriteParser::textureToSprites(tex, { 32,0 }, { 32,32 }, 4);
	clip->create(sprites, 0.3f);
	setClip(clip);
}

ExplodeEffect::~ExplodeEffect()
{
}
