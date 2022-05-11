#pragma once
#include "platform.h"
#include "renderer.h"

#define FLUF_ASSERT_PLATFORM() FLUF_ASSERT(App::Internal::platform, "Platform has not been created")
#define FLUF_ASSERT_RENDERER() FLUF_ASSERT(App::Internal::renderer, "Renderer has not been created")

namespace Fluf
{
	namespace App
	{
		namespace Internal
		{
			extern Platform* platform;
			extern Renderer* renderer;

			void iterate();
			void shutdown();
		}
	}
}