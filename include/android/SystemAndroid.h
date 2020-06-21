#ifndef SYSTEM_ANDROID_H
#define SYSTEM_ANDROID_H

#include "Constants.h"
#include "SystemBase.h"
#include "glad/glad.h"
#include <jni.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <string>


namespace System
{
	
	extern AAssetManager* NDK_ASSET_MANAGER;

	class SystemAndroid : public SystemBase
	{
		public:
			bool InitSystem() override;
			void Update() override;
			bool IsRunning() override;
			// TODO getsystemtype

			bool LoadBinaryDataFromAssets(const std::string fileName, unsigned char*& data, off_t& length) const override;
			bool LoadStringDataFromAssets(const std::string fileName, std::string& data) const override;
			//bool SetSystemAssetManager(AAssetManager *assetManager);
	};

	void SetSystemAssetManager(AAssetManager *assetManager);
    /*  System functions  */
	//bool InitSystemAndroid();
	
	//bool IsRunning();
	//void update();


	//bool LoadBinaryDataFromAssets(const std::string fileName, unsigned char*& data, off_t& length);
	//bool LoadStringDataFromAssets(const std::string fileName, std::string& data);
}

#endif // SYSTEM_ANDROID_H
