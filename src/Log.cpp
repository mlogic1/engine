#include "Log.h"

#ifdef _WIN32
#include <Windows.h>
#define FOREGROUND_YELLOW 0x0006
#define FOREGROUND_DEFAULT 0x0007
#endif

#ifdef __ANDROID__
#include <android/log.h>
#define APP_NAME "dungeon-platformer"
#endif

namespace Log
{
	void Write(std::string message, LogType logType)
	{
// Windows text color attributes
#ifdef _WIN32
		if (logType != LogType::STANDARD)
		{
			switch (logType)
			{
			case LogType::SUCCESS:
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
				break;
			case LogType::WARNING:
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_YELLOW);
				break;
			case LogType::ERR:
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
			default:
				break;
			}

		}
#endif

		std::cout << message << std::endl;

#ifdef __ANDROID__
		__android_log_print(ANDROID_LOG_VERBOSE, APP_NAME, message.c_str(), 1);
#endif

		// default Windows text color attributes
#ifdef _WIN32
		if (logType != LogType::STANDARD)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_DEFAULT);
		}
#endif
	}
}