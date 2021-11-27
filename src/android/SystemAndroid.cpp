#include "android/SystemAndroid.h"

#include "glad/glad.h"
#include "Log.h"
#include <EGL/egl.h>
#include <glad/glad.h>
#include <SceneManager.h>
#include <time.h>

namespace System
{
    AAssetManager* NDK_ASSET_MANAGER = nullptr;
    JNIEnv* JAVA_ENV = nullptr;

	bool SystemAndroid::InitSystem()
	{
		bool initSuccess = true;
		
        if(!gladLoadGLES2Loader((GLADloadproc)eglGetProcAddress))
        {
			Log::Write("Failed to initialize glad");
			initSuccess = false;
		}

        m_windowDimensions.Set(1920, 1080);
		return initSuccess;
	}

	void SystemAndroid::Update()
	{
		double currentTime = GetCurrentTime();
		m_deltaTime = (currentTime - prevTime) / 1000.0f;
		prevTime = currentTime;
		m_sceneManager->Update(m_deltaTime);
	}

	bool SystemAndroid::IsRunning()
	{
        // TODO fix android is running
        return true;
	}

	KeyState SystemAndroid::GetKeyState(const Key& key)
	{
		if (std::count(m_pressedKeys.cbegin(), m_pressedKeys.cend(), key) > 0)
		{
			return KeyState::PRESSED;
		}
		return KeyState::RELEASED;	// TODO
	}

	Vector2i SystemAndroid::GetWindowDimensions() const
	{
		return m_windowDimensions;
	}

    void SystemAndroid::SetWindowDimensions(Vector2i dimensions)
    {
	    m_windowDimensions = dimensions;
		m_viewport[0] = 0;
		m_viewport[1] = 0;
		m_viewport[2] = dimensions.x;
		m_viewport[3] = dimensions.y;
    }

	bool SystemAndroid::LoadBinaryDataFromAssets(const std::string fileName, unsigned char*& data, off_t& length) const
	{
        AAssetManager* manager = System::NDK_ASSET_MANAGER;
		// TODO missing file check
        AAsset* asset = AAssetManager_open(manager, fileName.c_str(), AASSET_MODE_UNKNOWN);
        length = AAsset_getLength(asset);

        data = new unsigned char[length + 1];
        AAsset_read(asset, data, length);
        data[length] = 0;
    	return true;
	}

	bool SystemAndroid::LoadStringDataFromAssets(const std::string fileName, std::string& data) const
	{
		std::string result = "";
		// TODO missing file check
		AAssetManager* manager = System::NDK_ASSET_MANAGER;

		AAsset* asset = AAssetManager_open(manager, fileName.c_str(), AASSET_MODE_UNKNOWN);
		off_t length;
		length = AAsset_getLength(asset);
		char* buffer = new char[length +1];
		AAsset_read(asset, buffer, length);
		AAsset_close(asset);
		buffer[length] = 0;


		data = std::string(buffer);
		delete[] buffer;

		std::string output;
		output.reserve(data.length());

		// strip carriage returns
		std::copy_if(data.begin(), data.end(),
					 std::back_inserter(output),
					 [] (char c) { return c != '\r'; });

		return true;
	}

	void SystemAndroid::SetCursorPosition(int x, int y)
	{
		// int viewport[4];
		// glGetIntegerv(GL_VIEWPORT, viewport);	// returns random values for some reason? using a cached value instead
		Vector2i windowDimensions = GetWindowDimensions();
		const int windowWidth = windowDimensions.x;
		const int windowHeight = windowDimensions.y;

		// Log::Write("Viewport: " + std::to_string(m_viewport[0]) + "\t" + std::to_string(m_viewport[1]) + "\t" + std::to_string(m_viewport[2]) + "\t" + std::to_string(m_viewport[3]));

		// convert to virtual resolution coordinates
		float cursorPosX = ((float)x / windowWidth) * VIRTUAL_RESOLUTION_WIDTH;
		float cursorPosY = ((float)y / windowHeight) * VIRTUAL_RESOLUTION_HEIGHT;
		// float cursorPosX = ((x - m_viewport[0]) / windowWidth) / (static_cast<float>(m_viewport[2]) / windowWidth) * VIRTUAL_RESOLUTION_WIDTH;
		// float cursorPosY = ((y - m_viewport[1]) / windowHeight) / (static_cast<float>(m_viewport[3]) / windowHeight) * VIRTUAL_RESOLUTION_HEIGHT;

		Log::Write("Engine update cursor pos: " + std::to_string(cursorPosX) + ", " + std::to_string(cursorPosY));

		m_cursorPosition.Set(cursorPosX, cursorPosY);
	}

	void SystemAndroid::OnCursorPressed(int x, int y)
	{
		m_pressedKeys.push_back(Key::CURSOR);
		SetCursorPosition(x, y);
	}

	void SystemAndroid::OnCursorReleased()
	{
		m_pressedKeys.erase(std::remove(m_pressedKeys.begin(), m_pressedKeys.end(), Key::CURSOR), m_pressedKeys.end());
		m_cursorPosition.Set(-1, -1);
	}

	double SystemAndroid::GetCurrentTime() const
	{
		struct timespec now;
		clock_gettime(CLOCK_REALTIME, &now);
		return 1000.0 * now.tv_sec + (double) now.tv_nsec / 1e6;
	}

	bool InitGameEngine()
	{
		SYSTEM_PTR = new SystemAndroid();
		SYSTEM_PTR->InitSystem();
		SYSTEM_PTR->InitSceneManager();
		SYSTEM_PTR->InitShaderManager();
		SYSTEM_PTR->InitTextureManager();
		SYSTEM_PTR->InitFontManager();
		SYSTEM_PTR->SetupEvents();
		return true;
	}

	void SetSystemAssetManager(AAssetManager *assetManager)
	{
		NDK_ASSET_MANAGER = assetManager;
	}

	void SetSystemEnvPointer(JNIEnv *env)
	{
		JAVA_ENV = env;
	}
}