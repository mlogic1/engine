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
		//SceneSystem::SceneManager::GetSceneManager()->Update();

		glfwSwapBuffers(m_gameWindow);
		glfwPollEvents();
	}

	bool SystemDesktop::IsRunning()
	{
		return !glfwWindowShouldClose(m_gameWindow);
	}

	bool SystemDesktop::LoadBinaryDataFromAssets(const std::string fileName, unsigned char *& data, off_t & length)
	{
		return false;
	}

	bool SystemDesktop::LoadStringDataFromAssets(const std::string fileName, std::string & data)
	{
		return false;
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
		//glfwSetKeyCallback(window, onKey);
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
		/*switch (_RenderMode)
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
		}*/
	}

	bool InitGameEngine()
	{
		SYSTEM_PTR = new SystemDesktop();
		return SYSTEM_PTR->InitSystem();
	}
}
