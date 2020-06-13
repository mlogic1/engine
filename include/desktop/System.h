#ifndef SYSTEM_H
#define SYSTEM_H

//#include <glad/glad.h>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Constants.h"

#include <string>

#define GLFW_GL_VERSION_MAJOR 3
#define GLFW_GL_VERSION_MINOR 3

namespace System
{
    /*  context */
	extern GLFWwindow* mainWindow;

	/*	rendering mode	*/
	enum GLRenderMode
	{
		LetterBox = 0,
		Virtual4By3 = 1,
		Stretch
	};

	extern GLRenderMode _RenderMode;

    /*  System functions  */
	bool InitSystemDesktop();
	bool IsRunning();
	void update();

	bool LoadBinaryDataFromAssets(const std::string fileName, unsigned char*& data, off_t& length);
	bool LoadStringDataFromAssets(const std::string fileName, std::string& data);
}

#endif // SYSTEM_H
