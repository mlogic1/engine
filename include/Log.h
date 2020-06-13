#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <string>

namespace Log
{
	enum LogType 
	{
		STANDARD = 0,
		SUCCESS,
		WARNING,
		ERR
	};
	void Write(std::string message, LogType logType = LogType::STANDARD);
}

#endif // !LOG_H