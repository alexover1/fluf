#pragma once
#include <fluf/common.h>

namespace Fluf
{
	struct Config;

	class Platform
	{
	public:
		virtual ~Platform() = default;

		// Initalize the Graphics
		virtual bool init(const Config& config) = 0;

		// Called after the on_startup callback, but before the update loop begins
		virtual void ready() = 0;

		// Called during shutdown
		virtual void shutdown() = 0;

		// The time, in ticks (microseconds) since the Application was started
		virtual u64 ticks() = 0;

		// Called once per frame
		virtual void update() = 0;

		// Sleeps the current thread
		virtual void sleep(int milliseconds) = 0;

		// Called to present the window contents
		virtual void present() = 0;

		// OpenGL Methods
		virtual void* gl_get_func(const char* name) = 0;
		virtual void* gl_context_create() = 0;
		virtual void gl_context_make_current(void* context) = 0;
		virtual void gl_context_destroy(void* context) = 0;

		// D3D11 Methods
		// TODO: add support for directx3d

		// Instantiates the Platform object
		static Platform* try_make_platform(const Config & config);
	};
}