#include "Component.h"
class Sprite;
class SpriteRenderer : public Component
{
public:
	SpriteRenderer();
	~SpriteRenderer();
public:
	void lateUpdate() override;
	void render(HDC hDC) override;
public:
	void setSprite(Sprite* sprite) { _sprite = sprite; }
	Sprite* getSprite() { return _sprite; }
private:
	Sprite* _sprite;
};