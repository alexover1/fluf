#pragma once
#include <fluf/graphics.h>
#include <fluf/drawing/static_sprite.h>
#include <deque>

namespace Fluf
{
	class Renderer
	{
	public:
		virtual void submit(const Renderable* renderable) = 0;
		virtual void flush() = 0;
	};

	class SimpleRenderer : public Renderer
	{
	private:
		std::deque<const StaticSprite*> m_render_queue;

	public:
		virtual void submit(const Renderable* renderable) override;
		virtual void flush() override;
	};
}