//
//  Shader.cpp
//  gl-tris
//
//  Created by mlogic1 on 24/12/2018.
//

#include "Shader.h"
#include "Constants.h"
#include "SystemBase.h"
#include <Log.h>

// helper function - TODO move to global functions
inline const GLint Shader::getCurrentProgramID()
{
	GLint id;
	glGetIntegerv(GL_CURRENT_PROGRAM, &id);
	return id;
}

/***************************************
 * public methods
***************************************/

Shader::Shader(std::string vertexShaderSourceFileName, std::string fragmentShaderSourceFileName)
{
	// load shaders
	std::string vertexShaderFilePath = PATH_SHADERS + vertexShaderSourceFileName;
	std::string fragmentShaderFilePath = PATH_SHADERS + fragmentShaderSourceFileName;

	System::SYSTEM_PTR->LoadStringDataFromAssets(vertexShaderFilePath, this->m_vertexShaderSource);
	System::SYSTEM_PTR->LoadStringDataFromAssets(fragmentShaderFilePath, this->m_fragmentShaderSource);
	//System::LoadStringDataFromAssets(vertexShaderFilePath, this->m_vertexShaderSource);
	//System::LoadStringDataFromAssets(fragmentShaderFilePath, this->m_fragmentShaderSource);

	// initialize shaders
	this->m_VERTEX_SHADER = glCreateShader(GL_VERTEX_SHADER);
	this->m_FRAGMENT_SHADER = glCreateShader(GL_FRAGMENT_SHADER);

	// compile shaders
	this->compileShaders();

	// create gl shader program and link shaders to shader program
	this->SHADER_ID = glCreateProgram();
	this->linkShaders();
	std::cout << "Successfully compiled shader " << this->SHADER_ID << std::endl;

	// clean up
	glDeleteShader(this->m_VERTEX_SHADER);
	glDeleteShader(this->m_FRAGMENT_SHADER);
}

Shader::~Shader()
{
	// clean up
	glDeleteProgram(this->SHADER_ID);
}

void Shader::useShader() const
{
	if (this->SHADER_ID != getCurrentProgramID())
	{
		glUseProgram(this->SHADER_ID);
	}
}

unsigned int Shader::getShaderID() const
{
	return this->SHADER_ID;
}

void Shader::set1i(const char* name, const int value) const
{
	if (this->SHADER_ID != getCurrentProgramID())
	{
		glUseProgram(this->SHADER_ID);
	}
	glUniform1i(glGetUniformLocation(this->SHADER_ID, name), value);
}

void Shader::set1f(const char* name, const float value) const
{
	if (this->SHADER_ID != getCurrentProgramID())
	{
		glUseProgram(this->SHADER_ID);
	}
	glUniform1f(glGetUniformLocation(this->SHADER_ID, name), value);
}

void Shader::setVec3f(const char *name, float x, float y, float z) const
{
	if (this->SHADER_ID != getCurrentProgramID())
	{
		glUseProgram(this->SHADER_ID);
	}
	glUniform3f(glGetUniformLocation(this->SHADER_ID, name), x, y, z);
}

void Shader::setMat4(const char* name, const glm::mat4 matrix) const
{
	if (this->SHADER_ID != getCurrentProgramID())
	{
		glUseProgram(this->SHADER_ID);
	}
	glUniformMatrix4fv(glGetUniformLocation(this->SHADER_ID, name), 1, GL_FALSE, glm::value_ptr(matrix));
}

/***************************************
 * private methods
***************************************/

void Shader::compileShaders()
{
	// vertex shader
	int success = false;    // compilation status flag

	const char *vertexShaderSource = this->m_vertexShaderSource.c_str();

	glShaderSource(this->m_VERTEX_SHADER, 1, &vertexShaderSource, NULL);
	glCompileShader(this->m_VERTEX_SHADER);

	glGetShaderiv(this->m_VERTEX_SHADER, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		std::string error = "Failed to compile vertex shader! Log: ";
		GLchar infoLog[1024];
		glGetShaderInfoLog(this->m_VERTEX_SHADER, 1024, NULL, infoLog);
		error += infoLog;
		throw error;
	}

	// fragment shader
	success = false;    // compilation status flag

	const char *fragmentShaderSource = this->m_fragmentShaderSource.c_str();

	glShaderSource(this->m_FRAGMENT_SHADER, 1, &fragmentShaderSource, NULL);
	glCompileShader(this->m_FRAGMENT_SHADER);

	glGetShaderiv(this->m_FRAGMENT_SHADER, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		std::string error = "Failed to compile fragment shader! Log: ";
		GLchar infoLog[1024];
		glGetShaderInfoLog(this->m_FRAGMENT_SHADER, 1024, NULL, infoLog);
		error += infoLog;
		throw error;
	}

}

void Shader::linkShaders()
{
	int success = false;
	glAttachShader(this->SHADER_ID, this->m_VERTEX_SHADER);
	glAttachShader(this->SHADER_ID, this->m_FRAGMENT_SHADER);

	glLinkProgram(SHADER_ID);

	glGetProgramiv(SHADER_ID, GL_LINK_STATUS, &success);
	if (!success) {
		GLchar infoLog[1024];
		glGetProgramInfoLog(SHADER_ID, 512, NULL, infoLog);
		std::string error = "Shader program linking failed!\n";
		error += infoLog;
		throw error;
	}
	std::cout << "Shader program successfully linked" << std::endl;

}
