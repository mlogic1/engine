//
//  GameCamera.h
//  gl-tris
//
//  Created by mlogic1 on 01/01/2019.
//

#ifndef GAMECAMERA_H
#define GAMECAMERA_H

#include <iostream>
#include <math.h>

#include <glm/glm.hpp>

#include "GameObject.h"
#include "Shader.h"

class GameCamera : public GameObject {

public:
	GameCamera();
	~GameCamera();

	/***************************************
	 *   inherited methods
	***************************************/
	void update(float deltaTime);
	void render();

	/***************************************
	 * Camera methods
	***************************************/
	glm::mat4 getMatrixView();
	glm::mat4 getProjection();

private:

	/***************************************
	 * camera configuration
	***************************************/
	glm::mat4 m_projection;   // projection matrix
	glm::mat4 m_view;         // view matrix

	/***************************************
	 * coordinates
	***************************************/
	glm::vec3 m_cameraPos;
	glm::vec3 m_cameraFront;
	glm::vec3 m_cameraUp;

	// FOV
	const float PROJECTION_FOV = 75.0f;

	// todo static initiation counter
	// if somebody tries to instantiate multiple cameras throw an exception
};

#endif /* GAMECAMERA_H */
