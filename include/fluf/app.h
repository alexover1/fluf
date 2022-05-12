#pragma once
#include <fluf/common.h>

#define FLUF_APP_OPTIONS_OPENGL_CONTEXT                 (1 << 0)
#define FLUF_APP_OPTIONS_FULLSCREEN                     (1 << 1)
#define FLUF_APP_OPTIONS_RESIZABLE                      (1 << 2)
#define FLUF_APP_OPTIONS_HIDDEN                         (1 << 3)
#define FLUF_APP_OPTIONS_WINDOW_POS_CENTERED            (1 << 4)

namespace fluf
{
	struct app_t;

	app_t* app_make(const char* name, int x, int y, int w, int h, u32 options);

	bool app_is_running();
	void app_stop_running();
	void app_update();
	void app_present();
	void app_destroy();
}