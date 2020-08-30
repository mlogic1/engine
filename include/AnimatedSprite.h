/**
    Animated Sprite
	@author mlogic1
	@date 29.08.2020.
*/

#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include "SceneObject.h"
#include "Shader.h"
#include "Rect.h"
#include <glad/glad.h>
#include <array>
#include <map>
#include <string>
#include <vector>

namespace Engine
{
	class AnimatedSprite : public SceneObject
	{

	public:
		AnimatedSprite(std::string objectID, Shader* spriteShader, Rect spriteRect, GLuint textureID, int frameCount, float frameTime, int frameWidth, int frameHeight, int textureRows, int textureCols, std::vector<SceneObject*> nestedObjects = {});
		~AnimatedSprite();

		/***************************************
		 * inherited methods
		***************************************/
		void update(float deltaTime) override;
		void render() override;

		/***************************************
		 * textures
		***************************************/
		void SetTexture(GLuint textureFileName, int frameCount, float frameTime, int frameWidth, int frameHeight, int textureRows, int textureCols);
		GLuint GetTexture();
		void PauseSpriteAnimation();
		void ResumeSpriteAnimation();
		void ResetSpriteAnimation();

	protected:
		void SetupTextureAtlas();

	protected:
		// texture
		GLuint m_texture;
		std::map< int, std::array<float, 8> > m_textureAtlas;
		uint32_t m_currentFrameIndex = 0;
		int m_frameCount;
		float m_frameTime;
		float m_currentFrameTime = 0;
		int m_frameWidth;
		int m_frameHeight;
		int m_spriteSheetRows;
		int m_spriteSheetCols;
		bool m_isAnimationRunning = true;

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
	};
}

#endif /* ANIMATED_SPRITE_H */
