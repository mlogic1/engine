cmake_minimum_required(VERSION 3.10.2)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(engine CXX C)

if (NOT ${CMAKE_SYSTEM_NAME} STREQUAL "Android")
	add_subdirectory(lib/glfw)
endif ()
add_subdirectory(lib/freetype)

SET (ENGINE_INCLUDE_DIR ./include)
SET (ENGINE_SOURCE_DIR ./src)
SET (GLAD_SOURCE_DIR ./lib/glad/src)

SET (STB_IMAGE_INCLUDE_DIR ./lib/stb_image)
SET (GLAD_INCLUDE_DIR ./lib/glad/include)
SET (GLM_INCLUDE_DIR ./lib/glm)
SET (JSON_INCLUDE_DIR ./lib/json)
SET (FREETYPE_INCLUDE_DIR ./lib/freetype/include)
SET (TINYXML2_INCLUDE_SRC_DIR ./lib/tinyxml2)

if (NOT ${CMAKE_SYSTEM_NAME} STREQUAL "Android")
	file(GLOB ENGINE_HEADER_FILES ${ENGINE_INCLUDE_DIR}/*.h ${ENGINE_INCLUDE_DIR}/desktop/*.h)
	file(GLOB ENGINE_SOURCE_FILES ${ENGINE_SOURCE_DIR}/*.cpp ${ENGINE_SOURCE_DIR}/desktop/*.cpp lib/glad/src/glad.c)
else()
	file(GLOB ENGINE_HEADER_FILES ${ENGINE_INCLUDE_DIR}/*.h ${ENGINE_INCLUDE_DIR}/android/*.h)
	file(GLOB ENGINE_SOURCE_FILES ${ENGINE_SOURCE_DIR}/*.cpp ${ENGINE_SOURCE_DIR}/android/*.cpp lib/glad/src/glad.c)
endif()
file(GLOB_RECURSE GLAD_SOURCE_FILES ${GLAD_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE TINYXML2_SOURCE_FILES ${TINYXML2_INCLUDE_SRC_DIR}/*.cpp)

include_directories(${ENGINE_INCLUDE_DIR})
include_directories(${STB_IMAGE_INCLUDE_DIR})
include_directories(${GLAD_INCLUDE_DIR})
include_directories(${GLM_INCLUDE_DIR})
include_directories(${JSON_INCLUDE_DIR})
include_directories(${FREETYPE_INCLUDE_DIR})
include_directories(${TINYXML2_INCLUDE_SRC_DIR})

SET (ENGINE_ALL_FILES
    ${ENGINE_HEADER_FILES}
    ${ENGINE_SOURCE_FILES}
	${GLAD_SOURCE_FILES}
    ${TINYXML2_SOURCE_FILES}
)

add_library(engine STATIC ${ENGINE_ALL_FILES})
target_include_directories(engine INTERFACE ${ENGINE_INCLUDE_DIR})
target_include_directories(engine INTERFACE ${STB_IMAGE_INCLUDE_DIR})
target_include_directories(engine INTERFACE ${GLAD_INCLUDE_DIR})
target_include_directories(engine INTERFACE ${GLM_INCLUDE_DIR})
target_include_directories(engine INTERFACE ${JSON_INCLUDE_DIR})
target_include_directories(engine INTERFACE ${FREETYPE_INCLUDE_DIR})
target_include_directories(engine PUBLIC ${TINYXML2_INCLUDE_SRC_DIR})

if (NOT ${CMAKE_SYSTEM_NAME} STREQUAL "Android")
	target_link_libraries(engine glfw)
endif()
target_link_libraries(engine freetype)