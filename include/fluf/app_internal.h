#pragma once
#include <fluf/app.h>
#include <SDL.h>

namespace fluf
{
	extern app_t* app;

	struct app_t
	{
		bool running = true;

		int x = 0;
		int y = 0;
		int w = 0;
		int h = 0;
		int options = 0;

		SDL_Window* window = nullptr;
	};
}
