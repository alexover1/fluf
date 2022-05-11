#pragma once
#include <fluf/common.h>

namespace Fluf
{
	// Application Event Functions
	using AppEventFn = Func<void>;

	// Application Configuration
	struct Config
	{
		// Application name.
		const char* name = "fluf";

		// Starting width, in pixels.
		// Depending on the OS DPI, the true window size may be a multiple of this.
		int width = 1280;

		// Starting height, in pixels.
		// Depending on the OS DPI, the true window size may be a multiple of this.
		int height = 720;

		// maximum updates to run before "giving up" and reducing frame rate.
		// this avoids the 'spiral of death'.
		// defaults to 5.
		int max_updates = 5;

		// target framerate.
		// defaults to 60.
		int target_framerate = 60;

		// Callback on application startup
		AppEventFn on_startup = nullptr;

		// Callback on application shutdown
		AppEventFn on_shutdown = nullptr;

		// Callback on application update
		AppEventFn on_update = nullptr;

		// Callback on application render
		AppEventFn on_render = nullptr;

		// Callback when the user has requested the application close.
		// For example, pressing the Close button, ALT+F4, etc
		// By default this calls `App::exit()`
		AppEventFn on_exit_request = nullptr;
	};

	// Application
	namespace App
	{
		// Runs the application
		bool run(const Config* config);

		// Checks if the Application is running yet
		bool is_running();

		// Exits the application.
		// This only signals for the application to close, it will not stop
		// until the current update and render calls are finished.
		void exit();

		// Gets the config data used to run the application
		const Config& config();
	}
}