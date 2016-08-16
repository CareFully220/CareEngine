#pragma once

#include <SDL2/SDL.h>
#include <string>


class Display
{
public:
	Display(int width, int height, const std::string& title);
	void Update();
	void Clear(float r, float g, float b, float a);
	bool IsClosed();

	inline int getWidth() { return m_iWidth; }
	inline int getHeight() { return m_iHeight; }

	virtual ~Display();
private:
	Display(const Display& other);
	void operator=(const Display& other);

	int m_iWidth;
	int m_iHeight;

	SDL_Window* m_window;
	SDL_GLContext m_glContext;
	bool m_bIsClosed;
};

