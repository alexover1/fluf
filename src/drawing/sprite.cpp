#include <fluf/drawing/sprite.h>

using namespace Fluf;

Sprite::Sprite(float x, float y, float width, float height, const Color& color)
	: Renderable(vec3{ x, y, 0 }, vec2{ width, height }, color)
{
}