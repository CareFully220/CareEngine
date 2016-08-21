#include "Window.h"
#include "ErrorHandler.h"

namespace CareEngine {

	Window::Window(int width, int height, const std::string& title, unsigned int flags)
		: m_iWidth(width), m_iHeight(height)
	{
		Uint32 windowFlags = SDL_WINDOW_OPENGL;

		if (flags & INVISIBLE)
		{
			windowFlags |= SDL_WINDOW_HIDDEN;
		}
		if (flags & FULLSCREEN)
		{
			windowFlags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}
		if (flags & BORDERLESS)
		{
			windowFlags |= SDL_WINDOW_BORDERLESS;
		}
		if (flags & VSYNC)
		{
			SDL_GL_SetSwapInterval(true);
		}

		m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_iWidth, m_iHeight, SDL_WINDOW_OPENGL);
		m_glContext = SDL_GL_CreateContext(m_window);

		GLenum status = glewInit();

		if (status != GLEW_OK)
		{
			ErrorHandler::sendError(ErrorHandler::ERR_FATAL, "OpenGL", "Glew failed to initialize!");
		}

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		// Print OpenGL version
		std::printf("[ OpenGL Version: %s ]\n", glGetString(GL_VERSION));
	}

	Window::~Window()
	{
		SDL_GL_DeleteContext(m_glContext);
		SDL_DestroyWindow(m_window);
		SDL_Quit();
	}

	void Window::SwapBuffer()
	{
		SDL_GL_SwapWindow(m_window);
	}

	void Window::Clear(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::setVSync(bool vsync)
	{
		SDL_GL_SetSwapInterval(vsync);
	}

}

