#ifndef CONSTANTS_H
#define CONSTANTS_H

/*	REQUIRED	*/
#define GAME_NAME "GAME"
#define STARTING_SCENE "Scene_Main_Menu"

#define ENGINE_FILE_FONTS "fonts.json"
#define ENGINE_FILE_SCENES "scenes.json"
#define ENGINE_FILE_SHADERS "shaders.json"
#define ENGINE_FILE_TEXTURES "textures.json"

#define VIRTUAL_RESOLUTION_WIDTH 1280
#define VIRTUAL_RESOLUTION_HEIGHT 720

// TODO: Refactor this - android has __linux__ defined

#if defined(__linux__) || defined(WIN32)
    #if defined(__ANDROID__)
        #define PATH_ASSETS ""
        #define PATH_SHADERS "shaders/"
        #define PATH_TEXTURES "textures/"
        #define PATH_FONTS "fonts/"
    #else
        #define PATH_ASSETS "assets/"
        #define PATH_SHADERS PATH_ASSETS "shaders/"
        #define PATH_TEXTURES PATH_ASSETS "textures/"
        #define PATH_FONTS PATH_ASSETS "fonts/"
        #define PATH_SCENES PATH_ASSETS "scenes/"
    #endif
#elif defined(__ANDROID__)
    #define PATH_SHADERS "shaders/"
    #define PATH_TEXTURES "textures/"
#else

#endif // defined


/*	OPTIONAL	*/


#endif // CONSTANTS_H
