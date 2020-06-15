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

Sprite::Sprite(Shader *spriteShader, Rect spriteRect, std::string textureFileName) :
	m_position(spriteRect.x, spriteRect.y),
	m_size(spriteRect.w, spriteRect.h),
	m_textureFileName(textureFileName)
{
	this->m_spriteShader = spriteShader;
	Log::Write("Instantiating sprite");

	loadTexture2D(textureFileName);
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


void Sprite::SetTexture(std::string textureFileName)
{
	loadTexture2D(textureFileName);
}

void Sprite::SetTexture(unsigned int glTexture)
{
	this->m_texture = glTexture;
}

std::string Sprite::GetTexture()
{
	return m_textureFileName;
}

unsigned int Sprite::GetTextureID()
{
	return this->m_texture;
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

void Sprite::loadTexture2D(std::string textureFileName)
{
	glGenTextures(1, &this->m_texture);
	glBindTexture(GL_TEXTURE_2D, this->m_texture);

	textureFileName = PATH_TEXTURES + textureFileName;

	int width, height, nOfChannels;

	stbi_set_flip_vertically_on_load(true);

	unsigned char* bufferData;
	off_t length;
	System::SYSTEM_PTR->LoadBinaryDataFromAssets(textureFileName, bufferData, length);

	unsigned char* data = stbi_load_from_memory(bufferData, length, &width, &height, &nOfChannels, 0);
    delete[] bufferData;

	if (!data)
	{
		std::string error = "Unable to load image: ";
		error += textureFileName;
		throw error;
	}
	else {
		std::cout << "Loaded image: " << textureFileName << std::endl;
	}

	// texture filtering options
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// enables transparency on png texture
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// generate texture
	if (nOfChannels == 4)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}
	else
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}

	glGenerateMipmap(GL_TEXTURE_2D);

	// clean up
	stbi_image_free(data);
}

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

