#include <fluf.h>
#include <string>

using namespace Fluf;

namespace
{
	void vec3_print(const vec3 v)
	{
		Log::info("vec3: (%f, %f, %f)", v[0], v[1], v[2]);
	}
}

namespace Test
{
	class Game
	{
	public:
		Shader* shader = nullptr;
		Batch* batch = nullptr;
		Vector<Sprite*> sprites;

		void startup()
		{
			std::string vertex =
				"#version 330 core\n"
				"layout(location = 0) in vec4 position;\n"
				"layout(location = 1) in vec4 color;\n"
				"uniform mat4 pr_matrix;\n"
				"uniform mat4 ml_matrix = mat4(1.0);\n"
				"out DATA\n"
				"{\n"
				"	vec4 position;\n"
				"	vec4 color;\n"
				"} vs_out;\n"
				"void main()\n"
				"{\n"
				"	gl_Position = pr_matrix * ml_matrix * position;\n"
				"	vs_out.position = ml_matrix * position;\n"
				"	vs_out.color = color;\n"
				"}\n";

			std::string fragment =
				"#version 330 core\n"
				"#extension GL_ARB_separate_shader_objects : enable\n"
				"layout(location = 0) out vec4 color;\n"
				"uniform vec2 light_pos;\n"
				"in DATA\n"
				"{\n"
				"	vec4 position;\n"
				"	vec4 color;\n"
				"} fs_in;\n"
				"void main()\n"
				"{\n"
				"	float intensity = 1.0 / length(fs_in.position.xy - light_pos);\n"
				"	color = fs_in.color * intensity;\n"
				"}\n";

			mat4x4 ortho{};
			mat4x4_ortho(ortho, 0, 16, 0, 9, -1, 1);

			shader = new Shader(vertex, fragment);
			shader->enable();
			shader->set_uniform_mat4("pr_matrix", ortho);
			shader->set_uniform_2f("light_pos", vec2{ 4.0f, 1.5f });

			batch = new Batch();

			// create sprites
			int amt = 0;
			for (float y = 0; y < 9.f; y += 0.1f)
				for (float x = 0; x < 16.f; x += 0.1f)
				{
					sprites.push_back(new Sprite(x, y, 0.08f, 0.08f, Color(0, rand() % 255, 255, 255)));
					amt++;
				}
			Log::info("Rendering %d Sprites using Batch Renderer", amt);
		}

		void render()
		{
			batch->begin();
			for (auto sprite : sprites)
			{
				batch->submit(sprite);
			}
			batch->end();
			batch->flush();
		}

		void shutdown()
		{
			delete batch;
			sprites.dispose();
			delete shader;
		}
	};
}

namespace
{
	Test::Game game;
}

int main()
{
	Config config;
	config.name = "fluf batch test";

	config.on_startup = []()
	{
		game.startup();
	};
	config.on_render = []()
	{
		game.render();
	};
	config.on_shutdown = []()
	{
		game.shutdown();
	};

	App::run(&config);
	return 0;
}