#include "android/SystemAndroid.h"

#include "glad/glad.h"
#include "Log.h"
#include <EGL/egl.h>
#include <glad/glad.h>
#include <SceneManager.h>

namespace System
{
    AAssetManager* NDK_ASSET_MANAGER = nullptr;


	bool SystemAndroid::InitSystem()
	{
		bool initSuccess = true;
		
        if(!gladLoadGLES2Loader((GLADloadproc)eglGetProcAddress))
        {
            Log::Write("Failed to initialize glad");
            initSuccess = false;
        }

		return initSuccess;
	}

	/*bool SystemAndroid::SetSystemAssetManager(AAssetManager* assetManager)
	{
        NDK_ASSET_MANAGER = assetManager;
		return  true;
	}*/

	bool SystemAndroid::IsRunning()
	{
        // TODO fix android is running
        return true;
	}

	void SystemAndroid::Update()
	{
        float dt = 0.0016f;
		m_sceneManager->Update(dt);
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

	bool InitGameEngine()
	{
		SYSTEM_PTR = new SystemAndroid();
		SYSTEM_PTR->InitSystem();
		SYSTEM_PTR->InitShaderManager();
		SYSTEM_PTR->InitTextureManager();

		return true;
	}

	void SetSystemAssetManager(AAssetManager *assetManager)
	{
		NDK_ASSET_MANAGER = assetManager;
	}
}
