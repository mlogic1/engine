#include "desktop/SystemDesktop.h"
#include <Constants.h>
#include <Log.h>

namespace System
{
	bool SystemDesktop::InitSystem()
	{
		bool initSuccess = true;
		initSuccess = glfwInit();
		if (!initSuccess)
		{
			Log::Write("Error initializing GLFW", Log::LogType::ERR);
			return initSuccess;
		}
		else
		{
			Log::Write("Init GLFW SUCCESS", Log::LogType::SUCCESS);
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_gameWindow = InitWindow();
		if (m_gameWindow == NULL)
			initSuccess = false;

		if (!initSuccess)
		{
			Log::Write("Error initializing GLFW Window", Log::LogType::ERR);
			glfwTerminate();
			return initSuccess;
		}

		initSuccess = InitGlad();

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		return initSuccess;
	}

	void SystemDesktop::Update()
	{
		glfwGetCursorPos(m_gameWindow, &m_mousePosition.x, &m_mousePosition.y);
		m_sceneManager.Update();

		m_fontManager->RenderTest("fonttest");

		glfwSwapBuffers(m_gameWindow);
		glfwPollEvents();
	}

	bool SystemDesktop::IsRunning()
	{
		return !glfwWindowShouldClose(m_gameWindow);
	}

	bool SystemDesktop::LoadBinaryDataFromAssets(const std::string fileName, unsigned char *& data, off_t & length) const
	{
		std::ifstream fileInStream(fileName, std::ios::binary);

		if (fileInStream.is_open())
		{
			fileInStream.ignore(std::numeric_limits<std::streamsize>::max());
			length = fileInStream.gcount();
			std::cout << "Loading file " << fileName << " | " << length << " bytes" << std::endl;

			fileInStream.seekg(0, std::ios_base::beg);

			char* buffer = new char[length + 1];
			fileInStream.read(buffer, length);
			buffer[length] = 0;
			data = (unsigned char*)buffer;

		}
		else
		{
			std::string error = "Missing file: " + fileName;
			throw error;
			return false;
		}

		fileInStream.close();
		return true;
	}

	bool SystemDesktop::LoadStringDataFromAssets(const std::string fileName, std::string & data) const
	{
		std::string result = "";

		std::ifstream fileInStream(fileName);

		std::string line;
		std::string temp = "";

		// load data from file
		std::cout << "Loading shader: " << fileName << std::endl;

		if (fileInStream.is_open())
		{
			while (fileInStream.good())
			{
				std::getline(fileInStream, line);
				temp += line + "\n";
			}
		}
		else
		{
			std::string error = "Missing file: " + fileName;
			throw error;
			return false;
		}

		data = temp;
		return true;
	}

	GLFWwindow * SystemDesktop::InitWindow()
	{
#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

		GLFWwindow* window = glfwCreateWindow(1280, 720, GAME_NAME, NULL, NULL);
		if (window == NULL)
		{
			Log::Write("Failed to create GLFW window", Log::LogType::WARNING);
			return NULL;
		}

		glfwMakeContextCurrent(window);
		glfwSetFramebufferSizeCallback(window, OnWindowResized);
		glfwSetKeyCallback(window, OnKey);
		return window;
	}

	bool SystemDesktop::InitGlad()
	{
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			Log::Write("Failed to initialize glad", Log::LogType::ERR);
			return false;
		}
		else
		{
			return true;
		}
	}

	void OnWindowResized(GLFWwindow * window, int width, int height)
	{
		switch (SYSTEM_PTR->GetRenderMode())
		{
		case GLRenderMode::LetterBox:
		{
			float currentAspect = (float)width / (float)height;
			float targetAspect = (float)VIRTUAL_RESOLUTION_WIDTH / (float)VIRTUAL_RESOLUTION_HEIGHT;

			GLsizei targetHeight = GLsizei(width / targetAspect + 0.5f);
			GLsizei targetWidth = 0;
			if (targetHeight > height)
			{
				targetHeight = height;
				targetWidth = GLsizei((float)height * targetAspect + 0.5f);
			}
			else
			{
				targetWidth = width;
			}

			int vpx = int(0.5f * (width - targetWidth));
			int vpy = int(0.5f * (height - targetHeight));
			glViewport(vpx, vpy, targetWidth, targetHeight);
			break;
		}

		case GLRenderMode::Virtual4By3:
		{
			// TODO
			glViewport(0, 0, width, height);
			break;
		}

		case GLRenderMode::Stretch:
		{
			glViewport(0, 0, width, height);
			break;
		}
		default:
			glViewport(0, 0, width, height);
			break;
		}
	}

	void OnKey(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		// TODO translate keys in a better way
		if (action == GLFW_PRESS)
		{
			Log::Write("Key Pressed: " + std::to_string(key));

			if (key == GLFW_KEY_ESCAPE)
				SYSTEM_PTR->ReceiveKeyInput(Key::ESC);

			if (key == GLFW_KEY_SPACE)
				SYSTEM_PTR->ReceiveKeyInput(Key::SPACE);

			if (key == GLFW_KEY_Q)
				SYSTEM_PTR->ReceiveKeyInput(Key::Q);
		}

		if (action == GLFW_RELEASE)
		{
			Log::Write("Key Released: " + std::to_string(key));
		}
	}

	bool InitGameEngine()
	{
		// TODO error checking
		SYSTEM_PTR = new SystemDesktop();
		SYSTEM_PTR->InitSystem();
		SYSTEM_PTR->InitShaderManager();
		SYSTEM_PTR->InitTextureManager();
		SYSTEM_PTR->InitFontManager();

		return true;
	}
}
