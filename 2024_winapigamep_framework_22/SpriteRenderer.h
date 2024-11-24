#include "Component.h"
class SpriteRenderer : public Component
{
public:
	SpriteRenderer();
	~SpriteRenderer();
public:
	void lateUpdate() override;
	void render(HDC _hdc) override;
};