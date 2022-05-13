#include <fluf.h>
#include <stdio.h>
#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_opengl3.h>

using namespace fluf;

namespace
{
	float size = 32;

	float positions[] =
	{
		0.0f, 0.0f, 0.0f, 1.0f, // 0
		size, 0.0f, 1.0f, 1.0f, // 1
		size, size, 1.0f, 0.0f, // 2
		0.0f, size, 0.0f, 0.0f, // 3
	};

	ushort indices[] =
	{
		0, 1, 2,
		2, 3, 0
	};

	int width = 320;
	int height = 180;

	int imgui_window_flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse;
}

int main()
{
	u32 options = 
		(FLUF_APP_OPTIONS_OPENGL_CONTEXT | 
		FLUF_APP_OPTIONS_RESIZABLE | 
		FLUF_APP_OPTIONS_WINDOW_POS_CENTERED | 
		FLUF_APP_OPTIONS_IMGUI);

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
	mat4x4 mat, translation;
	mat4x4_ortho(mat, 0, width, height, 0, -1, 1);
	mat4x4_translate(translation, 0, 0, 0);

	// create shader
	Shader shader("res/shaders/basic.shader");
	shader.enable();
	shader.set_uniform_1i("u_tex", 0); // the 0 needs to match the value passed in to texture.bind() (0 by default)
	shader.set_uniform_mat4("pr_matrix", mat);

	Renderer renderer;

	vec3 pos{ 200, 60, 0 };

	while (app_is_running())
	{
		app_update();

		// imgui
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();

		ImGui::SetNextWindowPos(ImVec2(10, 10));
		ImGui::Begin("My Menu", nullptr, imgui_window_flags);
		ImGui::SliderFloat3("Translation", pos, 0, 320 - size);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();

		// render
		mat4x4_translate(translation, pos[0], pos[1], pos[2]);
		shader.set_uniform_mat4("ml_matrix", translation);
		renderer.draw_triangles(va, ib, shader);

		ImGui::Render();
		
		app_present();
	}

	app_destroy();

	return 0;
}