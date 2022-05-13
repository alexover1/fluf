#include <fluf.h>
#include <stdio.h>

using namespace fluf;

namespace
{
	float size = 32;
	float x = 16;
	float y = 16;

	float positions[] =
	{
		x, y, 0.0f, 1.0f, // 0
		x+size, y, 1.0f, 1.0f, // 1
		x+size, y+size, 1.0f, 0.0f, // 2
		x, y+size, 0.0f, 0.0f, // 3
	};

	ushort indices[] =
	{
		0, 1, 2,
		2, 3, 0
	};

	int width = 320;
	int height = 180;
}

int main()
{
	u32 options = 0;
	options |= FLUF_APP_OPTIONS_OPENGL_CONTEXT;
	options |= FLUF_APP_OPTIONS_RESIZABLE;
	options |= FLUF_APP_OPTIONS_WINDOW_POS_CENTERED;

	app_t* app = app_make("fluffy game", 0, 0, 1280, 720, options);

	// create buffers
	vbuffer vb(positions, 4 * 4 * sizeof(float));
	ibuffer ib(indices, 6);
	varray va;

	vbufferlayout layout;
	layout.push<float>(2); // vec2 pos
	layout.push<float>(2); // vec2 tex_coord
	va.add_buffer(vb, layout);

	// load texture
	Texture texture("res/textures/smile.png");
	texture.bind();

	// create orthographic matrix
	mat4x4 mat;
	mat4x4_ortho(mat, 0, width, height, 0, -1, 1);

	// create shader
	Shader shader("res/shaders/basic.shader");
	shader.enable();
	//shader.set_uniform_4f("u_color", 0.0f, 0.3f, 0.8f, 1.0f );
	shader.set_uniform_1i("u_tex", 0); // the 0 needs to match the value passed in to texture.bind() (0 by default)
	shader.set_uniform_mat4("pr_matrix", mat);

	Renderer renderer;

	float r = 0.0f;
	float increment = 0.01f;

	while (app_is_running())
	{
		app_update();

		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		{
			// render
			renderer.draw_triangles(va, ib, shader);
			//shader.set_uniform_4f("u_color", r, 0.3f, 0.8f, 1.0f);

			// increment r component
			if (r > 1.0f)
				increment = -0.01f;
			else if (r < 0.0f)
				increment = 0.01f;

			r += increment;
		}
		
		app_present();
	}

	app_destroy();

	return 0;
}