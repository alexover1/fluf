#include <fluf/app.h>
#include <fluf/common.h>
#include <fluf/time.h>
#include "internal/internal.h"
#include "internal/platform.h"

using namespace Fluf;

#define FLUF_ASSERT_RUNNING() FLUF_ASSERT(app_is_running, "The App is not running (call App::run)")

// Internal Platform Pointer
Platform* App::Internal::platform = nullptr;

// Internal Renderer Pointer
Renderer* App::Internal::renderer = nullptr;

namespace
{
	// Global App State
	Config	   app_config;
	bool	   app_is_running = false;
	bool	   app_is_exiting = false;
	u64        app_time_last;
	u64        app_time_accumulator = 0;
}

bool App::run(const Config* c)
{
	FLUF_ASSERT(!app_is_running, "The Application is already running");

	// copy config
	app_config = *c;

	// default behaviour for exit_request to exit the application
	if (!app_config.on_exit_request)
		app_config.on_exit_request = App::exit;

	// exit out if setup is wrong
	FLUF_ASSERT(c != nullptr, "The Application requires a valid Config");
	FLUF_ASSERT(c->name != nullptr, "The Application Name cannot be null");
	FLUF_ASSERT(c->width > 0 && c->height > 0, "The Width and Height must be larget than 0");
	FLUF_ASSERT(c->max_updates > 0, "Max Updates must be >= 1");
	FLUF_ASSERT(c->target_framerate > 0, "Target Framerate must be >= 1");

	if (app_is_running || c == nullptr || c->width <= 0 || c->height <= 0 || c->max_updates <= 0 || c->target_framerate <= 0)
	{
		App::Internal::shutdown();
		return false;
	}

	// default values
	app_is_running = true;
	app_is_exiting = false;

	// initialize the system
	{
		Internal::platform = Platform::try_make_platform(app_config);
		if (!Internal::platform)
		{
			Log::error("Failed to create Platform module");
			App::Internal::shutdown();
			return false;
		}

		if (!Internal::platform->init(app_config))
		{
			Log::error("Failed to initialize Platform module");
			App::Internal::shutdown();
			return false;
		}
	}

	// initalize graphics
	{
		Internal::renderer = Renderer::try_make_renderer();
		if (!Internal::renderer)
		{
			Log::error("Failed to create Renderer module");
			App::Internal::shutdown();
			return false;
		}

		if (!Internal::renderer->init())
		{
			Log::error("Failed to initialize Renderer module");
			App::Internal::shutdown();
			return false;
		}
	}

	// startup
	if (app_config.on_startup != nullptr)
		app_config.on_startup();

	// display window
	Internal::platform->ready();

	// begin main loop
	while (!app_is_exiting)
		App::Internal::iterate();

	// shutdown
	if (app_config.on_shutdown != nullptr)
		app_config.on_shutdown();
	App::Internal::shutdown();
	return true;
}

bool App::is_running()
{
	return app_is_running;
}

void App::Internal::shutdown()
{
	if (platform)
		platform->shutdown();

	if (platform)
		delete platform;
	platform = nullptr;

	// clear static App state
	app_config = Config();
	app_is_running = false;
	app_is_exiting = false;
}

void App::Internal::iterate()
{
	// update at a fixed time step
	{
		u64 time_target = (u64)((1.0 / app_config.target_framerate) * Time::ticks_per_second);
		u64 time_curr = App::Internal::platform->ticks();
		u64 time_diff = time_curr - app_time_last;
		app_time_last = time_curr;
		app_time_accumulator += time_diff;

		// do not let us run too fast
		while (app_time_accumulator < time_target)
		{
			int milliseconds = (int)(time_target - app_time_accumulator) / (Time::ticks_per_second / 1000);
			App::Internal::platform->sleep(milliseconds);

			time_curr = App::Internal::platform->ticks();
			time_diff = time_curr - app_time_last;
			app_time_last = time_curr;
			app_time_accumulator += time_diff;
		}

		// Do not allow us to fall behind too many updates
		// (otherwise we'll get spiral of death)
		u64 time_maximum = app_config.max_updates * time_target;
		if (app_time_accumulator > time_maximum)
			app_time_accumulator = time_maximum;

		// do as many updates as we can
		while (app_time_accumulator >= time_target)
		{
			app_time_accumulator -= time_target;

			Time::delta = (1.0f / app_config.target_framerate);

			if (Time::pause_timer > 0)
			{
				Time::pause_timer -= Time::delta;
				if (Time::pause_timer <= -0.0001)
					Time::delta = -Time::pause_timer;
				else
					continue;
			}

			Time::previous_ticks = Time::ticks;
			Time::ticks += time_target;
			Time::previous_seconds = Time::seconds;
			Time::seconds += Time::delta;

			platform->update();
			renderer->update();

			if (app_config.on_update != nullptr)
				app_config.on_update();
		}
	}

	// render
	{
		renderer->before_render();

		if (app_config.on_render != nullptr)
			app_config.on_render();

		renderer->after_render();
		platform->present();
	}
}

void App::exit()
{
	FLUF_ASSERT_RUNNING();
	if (!app_is_exiting && app_is_running)
		app_is_exiting = true;
}

const Config& App::config()
{
	FLUF_ASSERT_RUNNING();
	return app_config;
}