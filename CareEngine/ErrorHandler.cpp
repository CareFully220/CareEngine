#include "ErrorHandler.h"
//#include "EngineController.h"
#include <SDL2\SDL.h>
#include <iostream>

namespace CareEngine {

	int ErrorHandler::m_lastErrorState = ERR_NONE;

	void ErrorHandler::sendError(int errType, const std::string& errorHeading, const std::string& errorText)
	{
		std::string error;
		switch (errType)
		{
		case ERR_FATAL:
			error = "Fatal Error: ";
			break;
		case ERR_WARNING:
			error = "Warning: ";
			break;
		case ERR_NOTIFY:
			error = "Note: ";
			break;
		};
		std::cerr << error << errorHeading << " --- " << errorText << std::endl;

		if (errType == ERR_FATAL)
		{
			terminateProgram();
		}
		m_lastErrorState = errType;
	}

	int ErrorHandler::getLastErrorState()
	{
		return m_lastErrorState;
	}

	void ErrorHandler::terminateProgram()
	{
		std::cout << "enter any character to force close the program!" << std::endl;
		char temp;
		std::cin >> temp;
		SDL_Quit();
		exit(1);
	}

}