//
//  GameCamera.cpp
//  gl-tris
//
//  Created by mlogic1 on 01/01/2019.
//

#include "GameCamera.h"

#include "Constants.h"
#include "Log.h"

/***************************************
 * public methods
***************************************/

GameCamera::GameCamera()
{
	Log::Write("Init game camera");

	// initial camera setup
	m_cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	m_cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	m_cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	m_projection = glm::perspective(glm::radians(PROJECTION_FOV), (float)VIRTUAL_RESOLUTION_WIDTH / (float)VIRTUAL_RESOLUTION_HEIGHT, 0.1f, 100.0f);
}

GameCamera::~GameCamera()
{
}

void GameCamera::update(float deltaTime)
{
	// projection and view matrix setup
	m_view = glm::mat4(1.0f);
	m_projection = glm::mat4(1.0f);

	m_projection = glm::perspective(glm::radians(PROJECTION_FOV), (float)VIRTUAL_RESOLUTION_WIDTH / (float)VIRTUAL_RESOLUTION_HEIGHT, 0.1f, 100.0f);
}

void GameCamera::render()
{
}

glm::mat4 GameCamera::getMatrixView()
{
	return glm::lookAt(m_cameraPos, m_cameraPos + m_cameraFront, m_cameraUp);
}

glm::mat4 GameCamera::getProjection()
{
	return m_projection;
}



