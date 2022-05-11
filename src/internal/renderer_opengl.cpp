#ifdef FLUF_RENDERER_OPENGL

#include "internal.h"
#include "renderer.h"
#include "platform.h"

#include <GL/glew.h>

namespace Fluf
{
	class OpenGL_Renderer : public Renderer
	{
	public:
		void* context;

		bool init() override;
		void shutdown() override;
		void update() override;
		void before_render() override;
		void after_render() override;
	};
}

using namespace Fluf;

bool OpenGL_Renderer::init()
{
	// create gl context
	context = App::Internal::platform->gl_context_create();
	if (context == nullptr)
	{
		Log::error("Failed to create OpenGL Context");
		return false;
	}
	App::Internal::platform->gl_context_make_current(context);

	if (glewInit() != GLEW_OK)
	{
		Log::error("Failed to initialize GLEW");
		return false;
	}

	return true;
}

void OpenGL_Renderer::shutdown()
{
	App::Internal::platform->gl_context_destroy(context);
	context = nullptr;
}

void OpenGL_Renderer::update()
{

}

void OpenGL_Renderer::before_render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGL_Renderer::after_render()
{

}

Renderer* Renderer::try_make_opengl()
{
	return new OpenGL_Renderer();
}

#endif // FLUF_RENDERER_OPENGL