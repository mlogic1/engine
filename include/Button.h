/**
    Button
	@author mlogic1
	@date 05.09.2020.
*/

#ifndef BUTTON_H
#define BUTTON_H

#include "SceneObject.h"
#include "Shader.h"
#include "Rect.h"
#include <glad/glad.h>
#include <map>
#include <string>
#include <vector>

namespace Engine
{
	enum class ButtonState
	{
		IDLE = 0,
		HOVER,
		PRESSED,
		DISABLED
	};

	class Button : public SceneObject
	{
	public:
		Button(std::string objectID, Shader* buttonShader, Rect buttonRect, std::map<ButtonState, GLuint> textureMap, const Vector2f& cursorPosition, std::vector<SceneObject*> nestedObjects = {});
		~Button();

		/***************************************
		 * inherited methods
		***************************************/
		void update(float deltaTime) override;
		void render() override;

		/***************************************
		 * textures
		***************************************/
		void SetTextureMap(std::map<ButtonState, GLuint> textureMap);
		const std::map<ButtonState, GLuint>& GetTextureMap();

	protected:
		// texture
		std::map<ButtonState, GLuint> m_textureMap;
		ButtonState m_currentButtonState;
		const Vector2f& m_cursorPosition;

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
		Shader* m_buttonShader;

	private:
		/*	default rect vertices count	*/
		unsigned int VERTEX_COUNT = 20;

		/*	default rect indices	*/
		const unsigned int m_indices[6] =
		{
			0, 1, 3,
			1, 2, 3
		};
	};
}

#endif /* BUTTON_H */
