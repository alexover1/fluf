#ifdef FLUF_PLATFORM_GLFW

#include "platform.h"
#include <fluf/app.h>
#include <fluf/common.h>
#include <fluf/time.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Fluf
{
	struct GLFW_Platform : public Platform
	{
		GLFWwindow* window;

		GLFW_Platform();
		bool init(const Config& config) override;
		void shutdown() override;
		u64 ticks() override;
		void update() override;
		void sleep(int milliseconds) override;
		void present() override;
	};
}

using namespace Fluf;

GLFW_Platform::GLFW_Platform()
{
	window = nullptr;
}

bool GLFW_Platform::init(const Config& config)
{
	// Initalize GLFW
	if (!glfwInit())
	{
		Log::error("Failed to initialize GLFW");
		return false;
	}

	// Create a window
	window = glfwCreateWindow(config.width, config.height, config.name, NULL, NULL);
	if (window == nullptr) 
	{
		Log::error("Failed to create a Window");
		return false;
	}

	// Create context
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	if (glewInit() != GLEW_OK)
	{
		Log::error("GLEW Failed to Initalize");
		exit(1);
	}
	
	// Enable VSYNC
	glfwSwapInterval(1.0);

	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* version = glGetString(GL_VERSION);

	Log::info("Renderer: %s", renderer);
	Log::info("OpenGL Version: %s", version);

	return true;
}

void GLFW_Platform::shutdown()
{
	if (window != nullptr)
		glfwDestroyWindow(window);
	window = nullptr;

	glfwTerminate();
}

u64 GLFW_Platform::ticks()
{
	return (u64)glfwGetTime();
}

void GLFW_Platform::update()
{
	if (glfwWindowShouldClose(window))
	{
		auto& config = App::config();
		if (config.on_exit_request != nullptr)
			config.on_exit_request();
	}
}

void GLFW_Platform::sleep(int milliseconds)
{
}

void GLFW_Platform::present()
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}

Platform* Platform::try_make_platform(const Config& config)
{
	return new GLFW_Platform();
}

#endif // FLUF_PLATFORM_GLFW