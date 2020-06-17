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

/***************************************
 * public methods
***************************************/

Sprite::Sprite(Shader *spriteShader, Rect spriteRect, GLuint textureID) :
	m_position(spriteRect.x, spriteRect.y),
	m_size(spriteRect.w, spriteRect.h),
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

bool Sprite::GetVisible()
{
	return m_isVisible;
}

Vector2f Sprite::GetPosition()
{
	return m_position;
}

Vector2f Sprite::GetSize()
{
	return m_size;
}

void Sprite::SetVisible(bool visibleState)
{
	m_isVisible = visibleState;
}

void Sprite::SetPosition(Vector2f position)
{
	m_position = position;
}

void Sprite::SetSize(Vector2f size)
{
	m_size = size;
}

/***************************************
 * private methods
***************************************/

void Sprite::GetNormalizedCoordinates(float (&arr)[20])
{
	float normX, normY;
	normX = (m_position.x - VIRTUAL_RESOLUTION_WIDTH / 2.0f) / (VIRTUAL_RESOLUTION_WIDTH / 2.0f);
	normY = (m_position.y - VIRTUAL_RESOLUTION_HEIGHT / 2.0f) / (VIRTUAL_RESOLUTION_HEIGHT / 2.0f);

	float normW, normH;
	normW = (m_position.x + m_size.x - VIRTUAL_RESOLUTION_WIDTH / 2.0f) / (VIRTUAL_RESOLUTION_WIDTH / 2.0f);
	normH = (m_position.y + m_size.y - VIRTUAL_RESOLUTION_HEIGHT / 2.0f) / (VIRTUAL_RESOLUTION_HEIGHT / 2.0f);

	float tlX = normX, tlY = normY * -1.0f;
	float trX = normW, trY = normY * -1.0f;

	float blX = normX, blY = normH * -1.0f;
	float brX = normW, brY = normH * -1.0f;

	float vertices[20] =
	{
		// position          // texture     // stride = 5 floats
		trX, trY,  1.0f,   1.0f, 1.0f,    // top right corner
		brX, brY, 1.0f,   1.0f, 0.0f,    // bottom right corner
		blX, blY, 1.0f,   0.0f, 0.0f,   // bottom left corner
		tlX, tlY,  1.0f,   0.0f, 1.0f    // top left corner
	};

	for (int i = 0; i < 20 ; ++i)
	{
		arr[i] = vertices[i];
	}
}

