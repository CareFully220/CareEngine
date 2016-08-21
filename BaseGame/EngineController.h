#pragma once
#include <memory>
#include <CareEngine/Window.h>
#include <SDL2/SDL.h>

class EngineController
{
public:
	EngineController();

	bool IsClosed() {
		return m_bClosed;
	}
	static void TerminateEngine();

	void MainLoop();

	~EngineController();
private:
	void BeginDraw();
	void EndDraw();
	void Update();

	void CalculateFps();

	CareEngine::Window* m_window;

	static bool m_bActive;
	static bool m_bClosed;
	
	float m_fps;
	float m_maxFps;
	float m_frameTime;

	EngineController(const EngineController& other);
	void operator=(const EngineController& other);
};
