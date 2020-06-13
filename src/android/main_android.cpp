// TODO init android

#include <jni.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include "Log.h"
#include "System.h"
#include "Constants.h"
#include <string>
#include <EventManager.h>
#include "SceneManager.h"
#include "SceneMainMenu.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

extern "C"
JNIEXPORT jint JNICALL
Java_com_github_mlogic1_dungeonplatformer_rendering_CppRenderer_AndroidMain(JNIEnv *env, jobject instance)
{
    /* initialize all systems   */
    Log::Write("Starting application | Android", Log::LogType::SUCCESS);

    // System
    if (!System::InitSystemAndroid())
    {
        Log::Write("Failed to initialize system", Log::LogType::ERR);
        return -1;
    }

    EventSystem::InitEventManager();

    SceneSystem::SceneManager::GetSceneManager()->SwitchScene(new SceneSystem::SceneMainMenu(STARTING_SCENE));

    /*while(System::IsRunning())
    {
        System::update();
    }*/

    return 0;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_github_mlogic1_dungeonplatformer_MainActivity_SetAssetManager(JNIEnv *env, jobject thiz, jobject manager)
{
    AAssetManager* assetManager = AAssetManager_fromJava(env, manager);
    System::SetSystemAssetManager(assetManager);
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_github_mlogic1_dungeonplatformer_rendering_CppRenderer_AndroidUpdate(JNIEnv *env, jobject thiz)
{
    System::update();
    return 0;
}