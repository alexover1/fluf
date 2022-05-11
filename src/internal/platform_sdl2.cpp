#ifdef FLUF_PLATFORM_SDL2

#include "platform.h"
#include <fluf/app.h>
#include <fluf/common.h>
#include <fluf/time.h>

#include <GL/glew.h>
#include <SDL.h>

// for File Reading / Writing
#include <filesystem>

#if _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>    // for the following includes
#include <winuser.h>	// for SetProcessDPIAware
#include <shellapi.h>	// for ShellExecute for dir_explore
#include <SDL_syswm.h>  // for SDL_SysWMinfo for D3D11
#endif

namespace Fluf
{
	void fluf_sdl_log(void* userdata, int category, SDL_LogPriority priority, const char* message)
	{
		if (priority <= SDL_LOG_PRIORITY_INFO)
			Log::info(message);
		else if (priority <= SDL_LOG_PRIORITY_WARN)
			Log::warn(message);
		else
			Log::error(message);
	}

	struct SDL2_Platform : public Platform
	{
		SDL_Window* window = nullptr;
		bool displayed = false;

		SDL2_Platform();
		bool init(const Config& config) override;
		void ready() override;
		void shutdown() override;
		u64 ticks() override;
		void update() override;
		void sleep(int milliseconds) override;
		void present() override;
		void* gl_get_func(const char* name) override;
		void* gl_context_create() override;
		void gl_context_make_current(void* context) override;
		void gl_context_destroy(void* context) override;
	};
}

using namespace Fluf;

SDL2_Platform::SDL2_Platform()
{
}

bool SDL2_Platform::init(const Config& config)
{
	// Required to call this for Windows
// I'm not sure why SDL2 doesn't do this on Windows automatically?
#if _WIN32
	SetProcessDPIAware();
#endif

	// TODO:
	// control this via some kind of config flag
	SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);
	SDL_LogSetOutputFunction(fluf_sdl_log, nullptr);

	// Get SDL version
	SDL_version version;
	SDL_GetVersion(&version);
	Log::info("SDL v%i.%i.%i", version.major, version.minor, version.patch);

	// initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_EVENTS | SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER) != 0)
	{
		Log::error("Failed to initialize SDL2");
		return false;
	}

	int flags = SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_HIDDEN | SDL_WINDOW_RESIZABLE;
	flags |= SDL_WINDOW_OPENGL; // TODO: add multiple types of renderers

	// Enable OpenGL
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// TODO:
	// This should be controlled via the gfx api somehow?
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

	// create the window
	window = SDL_CreateWindow(config.name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, config.width, config.height, flags);
	if (window == nullptr)
	{
		Log::error("Failed to create a Window");
		return false;
	}

#if _WIN32
	{
		// find the display index
		int display = SDL_GetWindowDisplayIndex(window);
		float ddpi, hdpi, vdpi;
		if (SDL_GetDisplayDPI(display, &ddpi, &hdpi, &vdpi) == 0)
		{
			// scale the window up basesd on the display DPI
			float hidpiRes = 96;
			float dpi = (ddpi / hidpiRes);
			if (dpi != 1)
			{
				SDL_DisplayMode mode;
				SDL_GetDesktopDisplayMode(display, &mode);
				SDL_SetWindowPosition(window, (int)(mode.w - config.width * dpi) / 2, (int)(mode.h - config.height * dpi) / 2);
				SDL_SetWindowSize(window, (int)(config.width * dpi), (int)(config.height * dpi));
			}
		}
	}
#endif

	// set window properties
	SDL_SetWindowResizable(window, SDL_TRUE);
	SDL_SetWindowMinimumSize(window, 256, 256);

	return true;
}

void SDL2_Platform::ready()
{
	SDL_GL_SetSwapInterval(1);
}

void SDL2_Platform::shutdown()
{
	if (window != nullptr)
		SDL_DestroyWindow(window);
	window = nullptr;
	displayed = false;

	SDL_Quit();
}

u64 SDL2_Platform::ticks()
{
	auto counter = SDL_GetPerformanceCounter();
	auto per_second = (double)SDL_GetPerformanceFrequency();
	return (u64)(counter * (Time::ticks_per_second / per_second));
}

void SDL2_Platform::update()
{
	// poll normal events
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			auto& config = App::config();
			if (config.on_exit_request != nullptr)
				config.on_exit_request();
		}
	}
}

void SDL2_Platform::sleep(int milliseconds)
{
	if (milliseconds >= 0)
		SDL_Delay((u32)milliseconds);
}

void SDL2_Platform::present()
{
	SDL_GL_SwapWindow(window);

	// display the window
	// this avoids a short black screen on macoS
	if (!displayed)
	{
		SDL_ShowWindow(window);
		displayed = true;
	}
}

void* SDL2_Platform::gl_get_func(const char* name)
{
	return SDL_GL_GetProcAddress(name);
}

void* SDL2_Platform::gl_context_create()
{
	void* pointer = SDL_GL_CreateContext(window);
	if (pointer == nullptr)
		Log::error("SDL_GL_CreateContext failed: %s", SDL_GetError());
	return pointer;
}

void SDL2_Platform::gl_context_make_current(void* context)
{
	SDL_GL_MakeCurrent(window, context);
}

void SDL2_Platform::gl_context_destroy(void* context)
{
	SDL_GL_DeleteContext(context);
}

Platform* Platform::try_make_platform(const Config& config)
{
	return new SDL2_Platform();
}


#endif // FLUF_PLATFORM_SDL2