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
        float currentFrame = static_cast<float>(glfwGetTime());
		m_deltaTime = currentFrame - lastFrame;
		deltaTimeAccumulated += m_deltaTime;
		lastFrame = currentFrame;
		UpdateCursorPosition();
		m_sceneManager->Update(m_deltaTime);

		glfwSwapBuffers(m_gameWindow);
		glfwPollEvents();

		++frameCounter;
		if (deltaTimeAccumulated > 0.01f)
		{
			m_FPS = frameCounter / deltaTimeAccumulated;
			frameCounter = 0;
			deltaTimeAccumulated = .0f;
		}
	}

	bool SystemDesktop::IsRunning()
	{
		return !glfwWindowShouldClose(m_gameWindow);
	}

	Vector2i SystemDesktop::GetWindowDimensions() const
	{
		int width, height;
		glfwGetWindowSize(m_gameWindow, &width, &height);
		return Vector2i(width, height);
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
		std::cout << "Loading file: " << fileName << std::endl;

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

	KeyState SystemDesktop::GetKeyState(const Key& key)
	{
		if (key == Key::CURSOR)
		{
			int state = glfwGetMouseButton(m_gameWindow, GLFW_MOUSE_BUTTON_LEFT);

			if (state == GLFW_PRESS)
			{
				return KeyState::PRESSED;
			}
		}

		return KeyState::RELEASED;
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
		glfwSetMouseButtonCallback(window, OnKeyMouse);
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

	void SystemDesktop::UpdateCursorPosition()
	{
		double cursorX, cursorY, invertedCursorY;
		int windowWidth, windowHeight;
		glfwGetWindowSize(m_gameWindow, &windowWidth, &windowHeight);
		glfwGetCursorPos(m_gameWindow, &cursorX, &cursorY);
		invertedCursorY = windowHeight - cursorY;

		int viewport[4];
		glGetIntegerv(GL_VIEWPORT, viewport);

		if (cursorX < 0.0f || cursorY < 0.0f || cursorX > windowWidth || cursorY > windowHeight)
		{
			m_cursorPosition.Set(-1.0f, -1.0f);
			return;
		}

		//Log::Write("VX: " + std::to_string(viewport[0]) + " VY: " + std::to_string(viewport[1]) + " VW: " + std::to_string(viewport[2]) + "VH: " + std::to_string(viewport[3]));

		if (cursorX < viewport[0] || cursorX > static_cast<double>(viewport[0]) + viewport[2] || invertedCursorY < viewport[1] || invertedCursorY > static_cast<double>(viewport[1]) + viewport[3])
		{
			m_cursorPosition.Set(-1.0f, -1.0f);
			return;
		}
		
		// normalize mouse between viewport
		float normalizedWindowCursorX = (cursorX) / (windowWidth);
		float normalizedWindowCursorY = (invertedCursorY) / (windowHeight);

		// float normalizedViewportCursorX = 

		float normalizedX = normalizedWindowCursorX * VIRTUAL_RESOLUTION_WIDTH;
		float normalizedY = normalizedWindowCursorY * VIRTUAL_RESOLUTION_HEIGHT;

		// BUG: If render mode is LetterBox and window was resized, mouse coordinates will be in window dimension instead of viewport dimensions
		// TODO: fix this by normalizing between viewport instead of virtual resolution
		// int viewport[4];
		// glGetIntegerv(GL_VIEWPORT, viewport);

		// set cursor position in virtual resolution corrdinates
		m_cursorPosition.Set(normalizedX, normalizedY);
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

			if (key == GLFW_KEY_W)
				SYSTEM_PTR->ReceiveKeyInput(Key::W);

			if (key == GLFW_KEY_A)
				SYSTEM_PTR->ReceiveKeyInput(Key::A);

			if (key == GLFW_KEY_S)
				SYSTEM_PTR->ReceiveKeyInput(Key::S);

			if (key == GLFW_KEY_D)
				SYSTEM_PTR->ReceiveKeyInput(Key::D);
			
			if (key == GLFW_KEY_0)
				SYSTEM_PTR->ReceiveKeyInput(Key::Num0);

			if (key == GLFW_KEY_1)
				SYSTEM_PTR->ReceiveKeyInput(Key::Num1);

			if (key == GLFW_KEY_2)
				SYSTEM_PTR->ReceiveKeyInput(Key::Num2);

			if (key == GLFW_KEY_3)
				SYSTEM_PTR->ReceiveKeyInput(Key::Num3);

			if (key == GLFW_KEY_4)
				SYSTEM_PTR->ReceiveKeyInput(Key::Num4);

			if (key == GLFW_KEY_5)
				SYSTEM_PTR->ReceiveKeyInput(Key::Num5);

			if (key == GLFW_KEY_6)
				SYSTEM_PTR->ReceiveKeyInput(Key::Num6);

			if (key == GLFW_KEY_7)
				SYSTEM_PTR->ReceiveKeyInput(Key::Num7);

			if (key == GLFW_KEY_8)
				SYSTEM_PTR->ReceiveKeyInput(Key::Num8);

			if (key == GLFW_KEY_9)
				SYSTEM_PTR->ReceiveKeyInput(Key::Num9);

		}

		if (action == GLFW_RELEASE)
		{
			Log::Write("Key Released: " + std::to_string(key));
		}
	}

	void OnKeyMouse(GLFWwindow* window, int key, int action, int mods)
	{
		if (action == GLFW_PRESS)
		{
			Log::Write("Key Pressed: " + std::to_string(key));

			if (key == GLFW_MOUSE_BUTTON_LEFT)
			{
				SYSTEM_PTR->ReceiveKeyInput(Key::CURSOR);
			}
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
		SYSTEM_PTR->InitSceneManager();
		SYSTEM_PTR->InitShaderManager();
		SYSTEM_PTR->InitTextureManager();
		SYSTEM_PTR->InitFontManager();

		return true;
	}
}
