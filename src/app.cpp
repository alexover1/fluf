#include <fluf/app.h>
#include <fluf/app_internal.h>

namespace fluf
{
	app_t* app;

#if defined DEBUG || defined _DEBUG
	void fluf_sdl_log(void* userdata, int category, SDL_LogPriority priority, const char* message)
	{
		if (priority <= SDL_LOG_PRIORITY_INFO)
			Log::info(message);
		else if (priority <= SDL_LOG_PRIORITY_WARN)
			Log::warn(message);
		else
			Log::error(message);
	}
#endif

	app_t* app_make(const char* name, int x, int y, int w, int h, u32 options)
	{
#if defined DEBUG || defined _DEBUG
		// LOGGING | TODO: remove
		SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);
		SDL_LogSetOutputFunction(fluf_sdl_log, nullptr);
#endif

		// get sdl version
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

		// set gl attributes
		if (options & FLUF_APP_OPTIONS_OPENGL_CONTEXT) {
			gl_set_attributes();
		}

		// window flags
		u32 flags = 0;
		if (options & FLUF_APP_OPTIONS_OPENGL_CONTEXT) flags |= SDL_WINDOW_OPENGL;
		if (options & FLUF_APP_OPTIONS_FULLSCREEN) flags |= SDL_WINDOW_FULLSCREEN;
		if (options & FLUF_APP_OPTIONS_RESIZABLE) flags |= SDL_WINDOW_RESIZABLE;
		if (options & FLUF_APP_OPTIONS_HIDDEN) flags |= (SDL_WINDOW_HIDDEN | SDL_WINDOW_MINIMIZED);

		// create window
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
		if (options & FLUF_APP_OPTIONS_OPENGL_CONTEXT)
		{
			SDL_GLContext ctx = gl_create_context(window);
			gl_init();

			if (options & FLUF_APP_OPTIONS_IMGUI)
				imgui_init(window, &ctx, "#version 330 core");
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
			if (app->imgui())
				ImGui_ImplSDL2_ProcessEvent(&event);

			if (event.type == SDL_QUIT)
			{
				app_stop_running();
				break;
			}
		}
	}

	void app_present()
	{
		if (app->imgui())
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (app->opengl())
			SDL_GL_SwapWindow(app->window);
	}

	void app_destroy()
	{
		if (app->imgui())
		{
			ImGui_ImplOpenGL3_Shutdown();
			ImGui_ImplSDL2_Shutdown();
			ImGui::DestroyContext();
		}

		if (app->window != nullptr)
			SDL_DestroyWindow(app->window);
		app->window = nullptr;

		SDL_Quit();
		delete app;
	}
}