#include <fluf.h>
#include <glad.h>
#include <stdio.h>

using namespace fluf;

namespace
{
	float positions[] =
	{
		-0.5f, -0.5f, // 0
		 0.5f, -0.5f, // 1
		 0.5f,  0.5f, // 2
		-0.5f,  0.5f, // 3
	};

	uint indices[] =
	{
		0, 1, 2,
		2, 3, 0
	};
}

int main()
{
	u32 options = 0;
	options |= FLUF_APP_OPTIONS_OPENGL_CONTEXT;
	options |= FLUF_APP_OPTIONS_RESIZABLE;
	options |= FLUF_APP_OPTIONS_WINDOW_POS_CENTERED;

	app_t* app = app_make("fluffy game", 0, 0, 1280, 720, options);

	// create buffers
	vbuffer vb(positions, 4 * 2 * sizeof(float));
	ibuffer ib(indices, 6);
	varray va;

	vbufferlayout layout;
	layout.push<float>(2);
	va.add_buffer(vb, layout);

	// create shader
	Shader shader("res/shaders/test.shader");
	shader.enable();

	glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

	while (app_is_running())
	{
		app_update();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// render loop
		va.bind();
		ib.bind();
		glDrawElements(GL_TRIANGLES, ib.count(), GL_UNSIGNED_INT, 0);
		ib.unbind();
		va.unbind();

		app_present();
	}

	app_destroy();

	return 0;
}