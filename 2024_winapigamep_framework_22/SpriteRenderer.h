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
	void setScale(const Vector2& scale) { _scale = scale; }
	const Vector2& getScale() { return _scale; }
private:
	Sprite* _sprite;
	Vector2 _scale;
};