#include "Button.h"
#include "SystemBase.h"
#include "Log.h"
#include "Constants.h"

namespace Engine
{
	/***************************************
	 * public methods
	***************************************/

	Button::Button(std::string objectID, Shader* ButtonShader, Rect ButtonRect, std::map<ButtonState, GLuint> textureMap, const Vector2f& cursorPosition, std::vector<SceneObject*> nestedObjects) :
		SceneObject(ButtonRect, objectID, nestedObjects),
		m_textureMap(textureMap),
		m_currentButtonState(ButtonState::IDLE),
		m_cursorPosition(cursorPosition)
	{
		this->m_buttonShader = ButtonShader;
		Log::Write("Instantiating Button");

		m_buttonShader->useShader();
		glUniform1i(glGetUniformLocation(this->m_buttonShader->getShaderID(), "sprite_texture"), 0);

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

	Button::~Button()
	{
	}

	void Button::update(float deltaTime)
	{
		SceneObject::update(deltaTime);

		float vertices[20];
		GetNormalizedCoordinates(vertices);

		glBindVertexArray(this->VAO);
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, 20 * sizeof(float), &vertices);

		const Vector2f worldPosition = GetWorldPosition();
		if (m_cursorPosition.x >= worldPosition.x && m_cursorPosition.y >= worldPosition.y && m_cursorPosition.x <= worldPosition.x + m_size.x && m_cursorPosition.y <= worldPosition.y + m_size.y)
		{
			// mouse inside button
			const System::KeyState keyState = System::SYSTEM_PTR->GetKeyState(System::Key::CURSOR);
			if (keyState == System::KeyState::PRESSED)
			{
				m_currentButtonState = ButtonState::PRESSED;
			}
			else
			{
				m_currentButtonState = ButtonState::HOVER;
			}
		}
		else
		{
			m_currentButtonState = ButtonState::IDLE;
		}
	}

	void Button::render()
	{
		glUseProgram(this->m_buttonShader->getShaderID());
		glBindVertexArray(this->VAO);
		glBindTexture(GL_TEXTURE_2D, m_textureMap.at(m_currentButtonState));
		
		glDrawElements(this->GL_DRAW_MODE, 6, GL_UNSIGNED_INT, 0);
		
		for (SceneObject* nestedObject : m_nestedObjects)
		{
			nestedObject->render();
		}
	}

	void Button::SetTextureMap(std::map<ButtonState, GLuint> textureMap)
	{
		m_textureMap = textureMap;
	}

	const std::map<ButtonState, GLuint>& Button::GetTextureMap()
	{
		return m_textureMap;
	}
}
