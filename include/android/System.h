#ifndef SYSTEM_H
#define SYSTEM_H

#include "glad/glad.h"
#include <jni.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <string>

#include "Constants.h"

#define GLFW_GL_VERSION_MAJOR 3
#define GLFW_GL_VERSION_MINOR 3

namespace System
{
	extern AAssetManager* NDK_ASSET_MANAGER;

    /*  System functions  */
	bool InitSystemAndroid();
	bool SetSystemAssetManager(AAssetManager *assetManager);
	bool IsRunning();
	void update();


	bool LoadBinaryDataFromAssets(const std::string fileName, unsigned char*& data, off_t& length);
	bool LoadStringDataFromAssets(const std::string fileName, std::string& data);
}

#endif // SYSTEM_H
