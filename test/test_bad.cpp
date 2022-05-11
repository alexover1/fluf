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
		SimpleRenderer* renderer = nullptr;
		Vector<StaticSprite*> sprites;

		void startup()
		{
			mat4x4 ortho{};
			mat4x4_ortho(ortho, 0, 16, 0, 9, -1, 1);
			
			shader = new Shader("res/shaders/basic.shader");
			shader->enable();
			shader->set_uniform_mat4("pr_matrix", ortho);

			renderer = new SimpleRenderer();

			// create sprites
			int amt = 0;
			for (float y = 0; y < 9.f; y += 0.1f)
				for (float x = 0; x < 16.f; x += 0.1f)
				{
					sprites.push_back(new StaticSprite(x, y, 0.08f, 0.08f, vec4{ 0, rand() % 1000 / 1000.f, 1, 1 }, *shader));
					amt++;
				}
			Log::info("Rendering %d Sprites using Simple Renderer", amt);
		}

		void render()
		{
			shader->enable();

			for (auto sprite : sprites)
				renderer->submit(sprite);
			renderer->flush();

			shader->disable();
		}

		void shutdown()
		{
			delete renderer;
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
	config.name = "my game";

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