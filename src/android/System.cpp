#include "System.h"

#include "glad/glad.h"
#include "Log.h"
//#include <iostream>
#include <EGL/egl.h>
#include <glad/glad.h>
#include <SceneManager.h>

namespace System
{
    AAssetManager* NDK_ASSET_MANAGER = nullptr;

    namespace
    {

    }

	bool InitSystemAndroid()
	{
		bool initSuccess = true;
		
        if(!gladLoadGLES2Loader((GLADloadproc)eglGetProcAddress))
        {
            Log::Write("Failed to initialize glad");
            initSuccess = false;
        }

		return initSuccess;
	}

	bool SetSystemAssetManager(AAssetManager* assetManager)
	{
        NDK_ASSET_MANAGER = assetManager;
		return  true;
	}

	bool IsRunning()
	{
        // TODO fix android is running
        return true;
	}

	void update()
	{
		SceneSystem::SceneManager::GetSceneManager()->Update();
	}

	bool LoadBinaryDataFromAssets(const std::string fileName, unsigned char*& data, off_t& length)
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

	bool LoadStringDataFromAssets(const std::string fileName, std::string& data)
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

}
