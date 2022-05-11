#include <fluf.h>
#include <string>
#include <fstream>
#include <iostream>

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
			mat4x4 ortho{};
			mat4x4_ortho(ortho, 0, 16, 0, 9, -1, 1);

			shader = new Shader("res/shaders/basic.shader");
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