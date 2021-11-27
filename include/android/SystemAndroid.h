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
	extern JNIEnv *JAVA_ENV;

	class SystemAndroid : public SystemBase
	{
		public:
			bool InitSystem() override;
			void Update() override;
			bool IsRunning() override;
			virtual KeyState GetKeyState(const Key& key) override;
			virtual Vector2i GetWindowDimensions() const override;
			void SetWindowDimensions(Vector2i dimensions);
			// TODO getsystemtype

			bool LoadBinaryDataFromAssets(const std::string fileName, unsigned char*& data, off_t& length) const override;
			bool LoadStringDataFromAssets(const std::string fileName, std::string& data) const override;
			//bool SetSystemAssetManager(AAssetManager *assetManager);

			void SetCursorPosition(int x, int y);
			void OnCursorPressed(int x, int y);
			void OnCursorReleased();

		private:
			double GetCurrentTime() const;

		private:
			Vector2i m_windowDimensions;
			std::vector<Key> m_pressedKeys;

			double prevTime = 0;
			int frameCounter = 0;

			int m_viewport[4];
	};

	void SetSystemEnvPointer(JNIEnv *env);
	void SetSystemAssetManager(AAssetManager *assetManager);
    /*  System functions  */
	// bool InitSystemAndroid();
}

#endif // SYSTEM_ANDROID_H
