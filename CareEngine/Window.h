#pragma once
#include <SDL2/SDL.h>
#include <GL\glew.h>
#include <string>

namespace CareEngine {

	enum WindowFlags {
		INVISIBLE = (1 << 0),
		FULLSCREEN = (1 << 1),
		BORDERLESS = (1 << 2),
		VSYNC = (1 << 3)
	};

	class Window
	{
	public:
		Window(int width, int height, const std::string& title, unsigned int currentFlags = 0);

		void SwapBuffer();
		void Clear(float r, float g, float b, float a);
		void setVSync(bool vsync);

		int getWidth() { return m_iWidth; }
		int getHeight() { return m_iHeight; }

		virtual ~Window();
	private:
		Window(const Window& other);
		void operator=(const Window& other);

		int m_iWidth;
		int m_iHeight;

		void processInput();

		SDL_Window* m_window;
		SDL_GLContext m_glContext;
	};


}