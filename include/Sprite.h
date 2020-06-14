//
//  Sprite.hpp
//  gl-tris
//
//  Created by mlogic1 on 29/12/2018.
//

#ifndef SPRITE_H
#define SPRITE_H

#include <glad/glad.h>
#include <iostream>
#include <vector>

#include "GameObject.h"
#include "Shader.h"
#include "Rect.h"

class Sprite : public GameObject {

public:

	Sprite(Shader *spriteShader, Rect spriteRect, std::string textureFileName);
	~Sprite();

	/***************************************
	 * inherited methods
	***************************************/
	void update(float deltaTime);
	void render();

	/***************************************
	 * textures
	***************************************/
	void SetTexture(std::string textureFileName);
	void SetTexture(unsigned int glTexture);
	std::string GetTexture();
	unsigned int GetTextureID();

	/***************************************
	 * properties
	***************************************/
	virtual bool GetVisible();
	Vector2f GetPosition();
	Vector2f GetSize();

	virtual void SetVisible(bool visibleState);
	void SetPosition(Vector2f position);
	void SetSize(Vector2f size);

protected:
	/*  texture loading method  */
	void loadTexture2D(std::string textureFileName);
	void GetNormalizedCoordinates(float(&arr)[20]);

protected:
	// properties
	bool m_isVisible = true;
	Vector2f m_position;
	Vector2f m_size;
	// TODO add pivots
	// TODO z-order

	// texture
	std::string m_textureFileName;
	unsigned int m_texture; // gl texture ID

private:
	/***************************************
	 * GL
	***************************************/

	// vertex array object
	unsigned int VAO;
	// vertex buffer object
	unsigned int VBO;
	// element buffer object
	unsigned int EBO;

	// draw mode
	const int GL_DRAW_MODE = GL_TRIANGLES;

	// shader
	Shader *m_spriteShader;

private:
	/*	default rect vertices count	*/
	unsigned int VERTEX_COUNT = 20;

	/*	default rect indices	*/
	const unsigned int m_indices[6] = {
		0, 1, 3,
		1, 2, 3
	};

	/* normalized texture coordinates TODO	*/
	const float texTRX = 1.0f;
	const float texTRY = 1.0f;
	const float texBRX = 1.0f;
	const float texBRY = 0.0f;
	const float texBLX = 0.0f;
	const float texBLY = 0.0f;
	const float texTLX = 0.0f;
	const float texTLY = 1.0f;

private:
	const std::string m_spriteID = "DefaultSprite";	// TODO every sprite needs a unique ID
};

#endif /* Sprite_h */
