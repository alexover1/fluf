#include <fluf.h>
#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_opengl3.h>
#include "test.h"
#include "test_clear_color.h"

using namespace fluf;
using namespace tests;

int main()
{
	u32 options =
		(FLUF_APP_OPTIONS_OPENGL_CONTEXT |
		FLUF_APP_OPTIONS_RESIZABLE |
		FLUF_APP_OPTIONS_WINDOW_POS_CENTERED |
		FLUF_APP_OPTIONS_IMGUI);

	app_t* app = app_make("fluffy game", 0, 0, 1280, 720, options);

	Test* current_test = nullptr;
	TestMenu* test_menu = new TestMenu(current_test);
	current_test = test_menu;

	test_menu->register_test<TestClearColor>("Clear Color");

	while (app_is_running())
	{
		app_update();

		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		// imgui
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();

		if (current_test)
		{
			current_test->on_update(0);
			current_test->on_render();

			ImGui::SetNextWindowPos(ImVec2(10, 10));
			ImGui::Begin("Test Menu");
			if (current_test != test_menu && ImGui::Button("<-"))
			{
				delete current_test;
				current_test = test_menu;
			}
			current_test->on_imgui_render();
			ImGui::End();
		}

		ImGui::Render();

		app_present();
	}

	// close test on exit
	if (current_test != test_menu)
		delete current_test;
	delete test_menu;

	app_destroy();
}