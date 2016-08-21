#include <iostream>
#include "EngineController.h"
#include <CareEngine/Shader.h>
#include <CareEngine/Model.h>
#include <CareEngine/Transform.h>
#include <CareEngine/Camera.h>
#include <CareEngine/ErrorHandler.h>

bool EngineController::m_bActive = true;
bool EngineController::m_bClosed = false;

EngineController::EngineController()
{
	m_window = new CareEngine::Window(1366, 768, "CareEngine", CareEngine::FULLSCREEN);
	m_maxFps = 120.0f;
}

EngineController::~EngineController()
{
	delete m_window;
}

void EngineController::MainLoop()
{
	// Initialize shaders
	CareEngine::Shader shader("./resource/shaders/basicShader");

	/*Vertex verticies[] = { Vertex(glm::vec3(0.0, -0.5, -0.5), glm::vec2(0.0, 0.0)),
	Vertex(glm::vec3(0.0, 0.5, -0.5), glm::vec2(0.5, 1.0)),
	Vertex(glm::vec3(0.0, 0.0, 0.5), glm::vec2(1.0, 0.0)) };

	unsigned int indices[] = { 0, 1, 2 };*/

	//	Mesh mesh(verticies, sizeof(verticies) / sizeof(verticies[0]), indices, sizeof(indices) / sizeof(indices[0]));
	CareEngine::Model model("./resource/models/bench.obj", "./resource/textures/Wood1.jpg");
	CareEngine::Model model2("./resource/models/bench.obj", "./resource/textures/Wood1.jpg");
	// Create default camera
	CareEngine::Camera camera(glm::vec3(-5.0, 0.0, 1.0), 70.0f, (float)m_window->getWidth() / (float)m_window->getHeight(), 0.01f, 1024.0f);

	CareEngine::Transform transform;
	CareEngine::Transform transform2;
	float counter = 0.0f;

	while (!m_bClosed)
	{
		// Used to limit fps
		float startTicks = SDL_GetTicks();

		BeginDraw();
		//float sinCounter = sinf(counter);
		float cosCounter = cosf(counter);

		shader.Bind();

		transform.getPos().x = sinf(counter);
		transform.getRot().z = counter;

		shader.Update(transform, camera);
		//mesh.Draw();
		model.Draw();

		shader.Update(transform2, camera);

		model2.Draw();

		Update();
		EndDraw();

		counter += 0.0005f;
		CalculateFps();
		// print only once per 60 frames
		static int frameCounter = 0;
		frameCounter++;
		if(frameCounter > 10)
		{ 
			std::cout << m_fps << std::endl;
			frameCounter = 0;
		}

		// Limit Fps
		float frameTicks = SDL_GetTicks() - startTicks;
		float maxTime = 1000.0f / m_maxFps;
		if (maxTime > frameTicks) {
			SDL_Delay(maxTime - frameTicks);
		}

		
	}
}

void EngineController::BeginDraw()
{
	m_window->Clear(0.0f, 0.0f, 0.0f, 1.0f);
}

void EngineController::EndDraw()
{
	m_window->SwapBuffer();
}

void EngineController::Update()
{
	SDL_Event e;

	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_QUIT:
			m_bClosed = true;
			break;
		/*case SDL_MOUSEMOTION:

			break;*/
		}
	}
}

void EngineController::CalculateFps()
{
	static const int NUM_SAMPLES = 10;
	static float frameTimes[NUM_SAMPLES];
	static int currentFrame = 0;
	static float prevTicks = SDL_GetTicks(); // Initialization happens only once

	float currentTicks = SDL_GetTicks();

	m_frameTime = currentTicks - prevTicks;
	frameTimes[currentFrame % NUM_SAMPLES] = m_frameTime;
	
	prevTicks = currentTicks;

	int count;

	currentFrame++;
	if (currentFrame < NUM_SAMPLES) 
		count = currentFrame;
	else 
		count = NUM_SAMPLES;
	float frameTimeAverage = 0;
	for (int i = 0; i < count; i++) {
		frameTimeAverage += frameTimes[i];
	}
	frameTimeAverage /= count;

	if (frameTimeAverage > 0)
	{
		m_fps = 1000.0f / frameTimeAverage;
	}
	else 
	{
		m_fps = 0.0f;
	}
	
}