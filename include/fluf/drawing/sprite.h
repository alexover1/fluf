#pragma once
#include <fluf/graphics.h>
#include <fluf/math/spatial.h>
#include <fluf/math/color.h>

namespace Fluf
{
	class Sprite : public Renderable
	{
	public:
		Sprite(float x, float y, float width, float height, const Color& color);
	};
}