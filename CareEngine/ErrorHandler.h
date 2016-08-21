#pragma once
#include <string>

namespace CareEngine {

	class ErrorHandler
	{
	public:
		enum
		{
			ERR_NONE,
			ERR_FATAL,
			ERR_WARNING,
			ERR_NOTIFY
		};

		static void sendError(int errType, const std::string& errorHeading, const std::string& errorText);

		static int getLastErrorState();
	private:
		static int m_lastErrorState;
		static void terminateProgram();
	};

}
