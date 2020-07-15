//
//  Sprite.cpp
//  gl-tris
//
//  Created by mlogic1 on 29/12/2018.
//

#include "Sprite.h"
#include "SystemBase.h"
#include "Log.h"
#include "Constants.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace Engine
{
	/***************************************
	 * public methods
	***************************************/

	Sprite::Sprite(Shader *spriteShader, Rect spriteRect, GLuint textureID) :
		SceneObject(spriteRect),
		m_texture(textureID)
	{
		this->m_spriteShader = spriteShader;
		Log::Write("Instantiating sprite");

		m_spriteShader->useShader();
		glUniform1i(glGetUniformLocation(this->m_spriteShader->getShaderID(), "sprite_texture"), 0);

		if (glGenVertexArrays == NULL)
		{
			Log::Write("Glgen not supported");
		}

		// generate buffers
		glGenVertexArrays(1, &this->VAO);
		glGenBuffers(1, &this->VBO);
		glGenBuffers(1, &this->EBO);

		// buffer data
		glBindVertexArray(this->VAO);
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);

		float vertices[20];
		GetNormalizedCoordinates(vertices);

		glBufferData(GL_ARRAY_BUFFER, 20 * sizeof(float), vertices, GL_STATIC_DRAW);

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(float), m_indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// load texture coordinates
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		// cleanup
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	Sprite::~Sprite()
	{
	}

	void Sprite::update(float deltaTime)
	{
		float vertices[20];
		GetNormalizedCoordinates(vertices);

		glBindVertexArray(this->VAO);
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, 20 * sizeof(float), &vertices);
	}

	void Sprite::render()
	{
		glUseProgram(this->m_spriteShader->getShaderID());
		glBindVertexArray(this->VAO);
		glBindTexture(GL_TEXTURE_2D, this->m_texture);

		glDrawElements(this->GL_DRAW_MODE, 6, GL_UNSIGNED_INT, 0);
	}

	void Sprite::SetTexture(GLuint textureID)
	{
		m_texture = textureID;
	}

	GLuint Sprite::GetTexture()
	{
		return m_texture;
	}

}
