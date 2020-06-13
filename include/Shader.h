/**
	Shader loads shader code and compiles it

	@author mlogic1
	@date 24.12.2018.
*/

#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <string>

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {

public:

	Shader(std::string vertexShaderSourceFileName, std::string fragmentShaderSourceFileName);
	~Shader();

	void useShader() const;
	unsigned int getShaderID() const;

	void set1i(const char* name, const int value) const;
	void set1f(const char* name, const float value) const;

	void setVec3f(const char* name, float x, float y, float z) const;
	void setMat4(const char* name, const glm::mat4 matrix) const;

private:

	/*  members  */

	// gl shader ID
	unsigned int SHADER_ID;

	// shader source code
	std::string m_vertexShaderSource;
	std::string m_fragmentShaderSource;

	// shader IDs
	unsigned int m_VERTEX_SHADER;
	unsigned int m_FRAGMENT_SHADER;

	/*  methods  */

	inline static const GLint getCurrentProgramID();

	void compileShaders();
	void linkShaders();

};

#endif /* SHADER_H */
