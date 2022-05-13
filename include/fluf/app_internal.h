#pragma once
#include <fluf/app.h>
#include <fluf/common.h>
#include <SDL.h>
#include <glad/glad.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl.h>
#include <imgui/imgui_impl_opengl3.h>

namespace fluf
{
	struct app_t
	{
		bool running = true;

		int x = 0;
		int y = 0;
		int w = 0;
		int h = 0;
		int options = 0;

		SDL_Window* window = nullptr;

		inline bool opengl()
		{
			return options & FLUF_APP_OPTIONS_OPENGL_CONTEXT;
		}

		inline bool imgui()
		{
			return options & FLUF_APP_OPTIONS_IMGUI;
		}
	};

	inline void gl_set_attributes()
	{
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	}

	inline SDL_GLContext gl_create_context(SDL_Window* window)
	{
		SDL_GLContext ctx = SDL_GL_CreateContext(window);
		if (!ctx)
		{
			Log::error("unable to create opengl context: %s", SDL_GetError());
			app_stop_running();
			return nullptr;
		}
		SDL_GL_MakeCurrent(window, ctx);

		return ctx;
	}

	inline void gl_init()
	{
		SDL_GL_SetSwapInterval(1);
		gladLoadGLLoader(SDL_GL_GetProcAddress);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glClearColor(0, 0, 0, 1);

		Log::info("OpenGL v%s", glGetString(GL_VERSION));
		Log::info("Renderer: %s", glGetString(GL_RENDERER));
	}

	inline void imgui_init(SDL_Window* window, SDL_GLContext* ctx, const char* glsl_version)
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImGui::StyleColorsDark();
		ImGui_ImplSDL2_InitForOpenGL(window, ctx);
		ImGui_ImplOpenGL3_Init(glsl_version);
	}
}
