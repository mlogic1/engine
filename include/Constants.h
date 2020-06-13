#ifndef CONSTANTS_H
#define CONSTANTS_H

/*	REQUIRED	*/
#define GAME_NAME "Dungeon Platformer"
#define STARTING_SCENE "Scene_Main_Menu"

#define VIRTUAL_RESOLUTION_WIDTH 1280
#define VIRTUAL_RESOLUTION_HEIGHT 720

#define PATH_ASSETS "assets/"

#if defined(__linux__) || defined(WIN32)
    #define PATH_SHADERS PATH_ASSETS "shaders/"
    #define PATH_TEXTURES PATH_ASSETS "textures/"
#elif defined(__ANDROID__)
    #define PATH_SHADERS "shaders/"
    #define PATH_TEXTURES "textures/"
#else

#endif // defined

/*	OPTIONAL	*/


#endif // CONSTANTS_H
