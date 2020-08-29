#include "AnimatedSprite.h"
#include "SystemBase.h"
#include "Log.h"
#include "Constants.h"

namespace Engine
{
	/***************************************
	 * public methods
	***************************************/

	AnimatedSprite::AnimatedSprite(std::string objectID, Shader* spriteShader, Rect spriteRect, GLuint textureID, int frameCount, float frameTime, int frameWidth, int frameHeight, int textureRows, int textureCols, std::vector<SceneObject*> nestedObjects) :
		SceneObject(spriteRect, objectID, nestedObjects),
		m_texture(textureID),
		m_frameCount(frameCount),
		m_frameTime(frameTime),
		m_frameWidth(frameWidth),
		m_frameHeight(frameHeight),
		m_spriteSheetRows(textureRows),
		m_spriteSheetCols(textureCols)
	{
		this->m_spriteShader = spriteShader;
		Log::Write("Instantiating animated sprite");

		int spriteSheetWidth = m_spriteSheetCols * m_frameWidth;
		int spriteSheetHeight = m_spriteSheetRows * m_frameHeight;

		// atlas setup
		int currentFrame = 0;
		for (int i = 0; i < m_spriteSheetRows; ++i)
		{
			for (int j = 0; j < m_spriteSheetCols; ++j)
			{
				int frameX = j * m_frameWidth;
				int frameY = i * m_frameHeight;

				float tlX = frameX / (float)spriteSheetWidth;
				float tlY = frameY / (float)spriteSheetHeight;
				float trX = (frameX + m_frameWidth) / (float)spriteSheetWidth;
				float trY = (frameY) / (float)spriteSheetHeight;
				float blX = frameX / (float)spriteSheetWidth;
				float blY = (frameY + m_frameHeight) / (float)spriteSheetHeight;
				float brX = (frameX + m_frameWidth) / (float)spriteSheetWidth;
				float brY = (frameY + m_frameHeight) / (float)spriteSheetHeight;

				// flip Y norm
				tlY = 1.0f - tlY;
				trY = 1.0f - trY;
				blY = 1.0f - blY;
				brY = 1.0f - brY;

				std::array<float, 8> normTexels = 
				{
					trX, trY,
					brX, brY,
					blX, blY,
					tlX, tlY
				};

				m_textureAtlas.emplace(currentFrame, normTexels);
				++currentFrame;
				if (currentFrame == m_frameCount) 
				{
					break;
				}
			}
		}

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

	AnimatedSprite::~AnimatedSprite()
	{
	}

	void AnimatedSprite::update(float deltaTime)
	{
		SceneObject::update(deltaTime);

		float vertices[20];
		GetNormalizedCoordinates(vertices);

		m_currentFrameTime += deltaTime;

		if (m_currentFrameTime >= m_frameTime)
		{
			m_currentFrameTime = .0f;
			++m_currentFrameIndex;
			if (m_currentFrameIndex >= m_frameCount)
			{
				m_currentFrameIndex = 0;
			}
		}

		std::array<float, 8> frameTexels = m_textureAtlas.at(m_currentFrameIndex);

		// normalized texel corrdinates
		vertices[3] = frameTexels[0];
		vertices[4] = frameTexels[1];
		vertices[8] = frameTexels[2];
		vertices[9] = frameTexels[3];
		vertices[13] = frameTexels[4];
		vertices[14] = frameTexels[5];
		vertices[18] = frameTexels[6];
		vertices[19] = frameTexels[7];

		glBindVertexArray(this->VAO);
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, 20 * sizeof(float), &vertices);
	}

	void AnimatedSprite::render()
	{
		glUseProgram(this->m_spriteShader->getShaderID());
		glBindVertexArray(this->VAO);
		glBindTexture(GL_TEXTURE_2D, this->m_texture);
		
		glDrawElements(this->GL_DRAW_MODE, 6, GL_UNSIGNED_INT, 0);
		
		for (SceneObject* nestedObject : m_nestedObjects)
		{
			nestedObject->render();
		}
	}

	void AnimatedSprite::SetTexture(GLuint textureID)
	{
		m_texture = textureID;
	}

	GLuint AnimatedSprite::GetTexture()
	{
		return m_texture;
	}
}
