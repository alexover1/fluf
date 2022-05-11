#pragma once
#include <fluf/common.h>

namespace Fluf
{
	struct Config;

	class Renderer
	{
	public:
		virtual ~Renderer() = default;

		// Initalize the Graphics
		virtual bool init() = 0;

		// Called during shutdown
		virtual void shutdown() = 0;

		// Called once per frame
		virtual void update() = 0;

		// Called once per frame before render 
		virtual void before_render() = 0;

		// Called once per frame after render 
		virtual void after_render() = 0;

	private:
		static Renderer* try_make_opengl();
		static Renderer* try_make_d3d11();

	public:
		static Renderer* try_make_renderer()
		{
			return try_make_opengl();
		}
	};
}