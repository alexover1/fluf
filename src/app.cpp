#include <fluf/app.h>
#include <fluf/app_internal.h>
#include <glad/glad.h>

namespace fluf
{
	app_t* app;

	void fluf_sdl_log(void* userdata, int category, SDL_LogPriority priority, const char* message)
	{
		if (priority <= SDL_LOG_PRIORITY_INFO)
			Log::info(message);
		else if (priority <= SDL_LOG_PRIORITY_WARN)
			Log::warn(message);
		else
			Log::error(message);
	}

	app_t* app_make(const char* name, int x, int y, int w, int h, u32 options)
	{
		// LOGGING
		SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);
		SDL_LogSetOutputFunction(fluf_sdl_log, nullptr);

		// Get SDL version
		SDL_version version;
		SDL_GetVersion(&version);
		Log::info("SDL v%i.%i.%i", version.major, version.minor, version.patch);

		// initialize sdl
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_EVENTS) != 0)
		{
			Log::error("failed to init sdl");
			app_stop_running();
			return nullptr;
		}

		u32 flags = 0;
		if (options & FLUF_APP_OPTIONS_OPENGL_CONTEXT) flags |= SDL_WINDOW_OPENGL;
		if (options & FLUF_APP_OPTIONS_FULLSCREEN) flags |= SDL_WINDOW_FULLSCREEN;
		if (options & FLUF_APP_OPTIONS_RESIZABLE) flags |= SDL_WINDOW_RESIZABLE;
		if (options & FLUF_APP_OPTIONS_HIDDEN) flags |= (SDL_WINDOW_HIDDEN | SDL_WINDOW_MINIMIZED);

		if (options & FLUF_APP_OPTIONS_OPENGL_CONTEXT) {
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		}

		SDL_Window* window;
		if (options & FLUF_APP_OPTIONS_WINDOW_POS_CENTERED) {
			window = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, flags);
		}
		else {
			window = SDL_CreateWindow(name, x, y, w, h, flags);
		}

		// create app
		app_t* app = new app_t();
		app->options = options;
		app->window = window;
		app->w = w;
		app->h = h;
		app->x = x;
		app->y = y;
		fluf::app = app;

		// initialize opengl
		if ((options & FLUF_APP_OPTIONS_OPENGL_CONTEXT))
		{
			SDL_GLContext ctx = SDL_GL_CreateContext(window);
			if (!ctx) 
			{
				Log::error("unable to create opengl context: %s", SDL_GetError());
				app_stop_running();
				return nullptr;
			}
			SDL_GL_SetSwapInterval(1);
			SDL_GL_MakeCurrent(window, ctx);
			gladLoadGLLoader(SDL_GL_GetProcAddress);

			// TODO: should this go here?
			// maybe this should be in the same place as where you would call glClearColor... etc
			// some kind of gl settings function
			// blending
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			Log::info("OpenGL v%s", glGetString(GL_VERSION));
			Log::info("Renderer: %s", glGetString(GL_RENDERER));
		}

		return app;
	}

	bool app_is_running()
	{
		return app->running;
	}

	void app_stop_running()
	{
		app->running = false;
	}

	void app_update()
	{
		// poll normal events
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				app_stop_running();
				break;
			}
		}
	}

	void app_present()
	{
		if (app->options & FLUF_APP_OPTIONS_OPENGL_CONTEXT)
		{
			SDL_GL_SwapWindow(app->window);
		}
	}

	void app_destroy()
	{
		if (app->window != nullptr)
			SDL_DestroyWindow(app->window);
		app->window = nullptr;

		SDL_Quit();
		delete app;
	}
}