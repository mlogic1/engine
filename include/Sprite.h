/**
    Sprite
	@author mlogic1
	@date 29.12.2018.
*/

#ifndef SPRITE_H
#define SPRITE_H

#include "SceneObject.h"
#include "Shader.h"
#include "Rect.h"
#include <glad/glad.h>
#include <iostream>
#include <vector>

namespace Engine
{
	class Sprite : public SceneObject 
	{

	public:
		Sprite(Shader* spriteShader, Rect spriteRect, GLuint textureID);
		~Sprite();

		/***************************************
		 * inherited methods
		***************************************/
		void update(float deltaTime) override;
		void render() override;

		/***************************************
		 * textures
		***************************************/
		void SetTexture(GLuint textureFileName);
		GLuint GetTexture();

	protected:
		/*  normalize  */
		void GetNormalizedCoordinates(float(&arr)[20]);

	protected:
		// texture
		GLuint m_texture; // gl texture ID

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
		Shader* m_spriteShader;

	private:
		/*	default rect vertices count	*/
		unsigned int VERTEX_COUNT = 20;

		/*	default rect indices	*/
		const unsigned int m_indices[6] = 
		{
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
}

#endif /* Sprite_h */
