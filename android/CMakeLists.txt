cmake_minimum_required(VERSION 3.10.2)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(D:/Programming/cpp/projects/engine/lib/freetype build_freetype)
add_subdirectory(D:/Programming/cpp/projects/engine/lib/oboe build_oboe)

project(engine CXX C)

SET (ENGINE_INCLUDE_DIR ../include)
SET (ENGINE_SOURCE_DIR ../src)
SET (GLAD_SOURCE_DIR ../lib/glad/src)

SET (STB_IMAGE_INCLUDE_DIR ../lib/stb_image)
SET (GLAD_INCLUDE_DIR ../lib/glad/include)
SET (GLM_INCLUDE_DIR ../lib/glm)
SET (JSON_INCLUDE_DIR ../lib/json)
SET (FREETYPE_INCLUDE_DIR ../lib/freetype/include)
SET (OBOE_INCLUDE_DIR ../lib/oboe/include)

file(GLOB ENGINE_HEADER_FILES ${ENGINE_INCLUDE_DIR}/*.h ${ENGINE_INCLUDE_DIR}/android/*.h)
file(GLOB ENGINE_SOURCE_FILES ${ENGINE_SOURCE_DIR}/*.cpp ${ENGINE_SOURCE_DIR}/android/*.cpp ${GLAD_SOURCE_DIR}/glad.c)
file(GLOB_RECURSE GLAD_SOURCE_FILES ${GLAD_SOURCE_DIR}/*.cpp)

include_directories(${ENGINE_INCLUDE_DIR})
include_directories(${STB_IMAGE_INCLUDE_DIR})
include_directories(${GLAD_INCLUDE_DIR})
include_directories(${GLM_INCLUDE_DIR})
include_directories(${JSON_INCLUDE_DIR})
include_directories(${FREETYPE_INCLUDE_DIR})

SET (ENGINE_ALL_FILES
    ${ENGINE_HEADER_FILES}
    ${ENGINE_SOURCE_FILES}
	${GLAD_SOURCE_FILES}
)

add_library(engine STATIC ${ENGINE_ALL_FILES})
target_include_directories(engine INTERFACE ${ENGINE_INCLUDE_DIR})
target_include_directories(engine INTERFACE ${STB_IMAGE_INCLUDE_DIR})
target_include_directories(engine INTERFACE ${GLAD_INCLUDE_DIR})
target_include_directories(engine INTERFACE ${GLM_INCLUDE_DIR})
target_include_directories(engine INTERFACE ${JSON_INCLUDE_DIR})
target_include_directories(engine INTERFACE ${FREETYPE_INCLUDE_DIR})
target_include_directories(engine INTERFACE ${OBOE_INCLUDE_DIR})

target_link_libraries(engine freetype)
target_link_libraries(engine oboe)