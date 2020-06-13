#include "desktop/System.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Log.h"
#include <iostream>
#include <fstream>
#include <SceneManager.h>

namespace System
{
	// rendering mode // TODO maybe move this to a global configuration source file
	GLRenderMode _RenderMode = GLRenderMode::LetterBox;
	GLFWwindow* mainWindow = nullptr;

    namespace
    {
        void onWindowResized(GLFWwindow* window, int width, int height)
        {
			switch (_RenderMode)
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

        void onKey(GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            if (key == GLFW_KEY_Q && action == GLFW_RELEASE)
			{
                glfwSetWindowShouldClose(window, true);
            }

            if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE)
			{
				
            }

			if (key == GLFW_KEY_A && action == GLFW_RELEASE)
			{
				SceneSystem::SceneManager::GetSceneManager()->OnKey(Key::A);
			}
        }

        GLFWwindow* InitWindow()
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
            glfwSetFramebufferSizeCallback(window, onWindowResized);
            glfwSetKeyCallback(window, onKey);
            return window;
        }

        int initGlad()
        {
            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            {
                Log::Write("Failed to initialize glad", Log::LogType::ERR);
                return -1;
            }
            else
            {
                return 1;
            }
        }
    }

	bool InitSystemDesktop()
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

        System::mainWindow = InitWindow();
        if (System::mainWindow == NULL)
            initSuccess = false;

		if(!initSuccess)
		{
			Log::Write("Error initializing GLFW Window", Log::LogType::ERR);
            glfwTerminate();
			return initSuccess;
		}

        initSuccess = initGlad();

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
		return initSuccess;
	}

	bool IsRunning()
	{
        return !glfwWindowShouldClose(System::mainWindow);
	}

	void update()
	{
		SceneSystem::SceneManager::GetSceneManager()->Update();

		glfwSwapBuffers(mainWindow);
		glfwPollEvents();
	}

	bool LoadBinaryDataFromAssets(const std::string fileName, unsigned char*& data, off_t& length)
	{
		std::ifstream fileInStream(fileName, std::ios::binary);

		if (fileInStream.is_open())
		{
            fileInStream.ignore(std::numeric_limits<std::streamsize>::max());
			length = fileInStream.gcount();
			std::cout<<"Loading file "<< fileName << " | " <<length << " bytes" <<std::endl;

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

	bool LoadStringDataFromAssets(const std::string fileName, std::string& data)
	{
        std::string result = "";

		std::ifstream fileInStream(fileName);

		std::string line;
		std::string temp = "";

		// load data from file
		std::cout << "Loading shader: " << fileName << std::endl;

		if (fileInStream.is_open())
		{
			while(fileInStream.good())
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

}
