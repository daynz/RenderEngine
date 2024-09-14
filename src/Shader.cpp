#include "Shader.hpp"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

Shader::Shader(std::string vertexPath, std::string fragmentPath)
{
	std::ifstream vertexFile, fragmentFile;
	
	vertexFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragmentFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	std::string vertexCode;
	std::string fragmentCode;
	try
	{
		vertexFile.open(vertexPath);
		fragmentFile.open(fragmentPath);

		std::stringstream vertexStream, fragmentStream;
		vertexStream << vertexFile.rdbuf();
		fragmentStream << fragmentFile.rdbuf();

		vertexFile.close();
		fragmentFile.close();

		vertexCode = vertexStream.str();
		fragmentCode = fragmentStream.str();
		
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "Error::Shader::file_not_successfully_read" << std::endl;
		std::cout << "VertexShader: " << vertexPath << " FragmentShader" << fragmentPath << std::endl;
	}
	const char* vCode = vertexCode.c_str();
	const char* fCode = fragmentCode.c_str();

	unsigned int vertex, fragment;

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vCode, NULL);
	glCompileShader(vertex);
	checkCompileError(vertex, "VERTEX");

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fCode, NULL);
	glCompileShader(fragment);
	checkCompileError(fragment, "FRAGMENT");

	m_ID = glCreateProgram();
	glAttachShader(m_ID, vertex);
	glAttachShader(m_ID, fragment);
	glLinkProgram(m_ID);
	checkCompileError(m_ID, "PROGRAM");

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

Shader::Shader(std::string vertexPath, std::string fragmentPath, std::string geometryPath)
	:Shader(vertexPath, fragmentPath)
{
	std::ifstream geometryFile;

	geometryFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	std::string geometryCode;

	try
	{
		geometryFile.open(geometryPath);

		std::stringstream geometryStream;
		geometryStream << geometryFile.rdbuf();

		geometryFile.close();

		geometryCode = geometryStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "Error::Shader::file_not_successfully_read" << std::endl;
		std::cout << "VertexShader: " << vertexPath << " FragmentShader" << fragmentPath <<" GeometryShader" << geometryPath << std::endl;
	}
	const char* gCode = geometryCode.c_str();

	unsigned int geometry;

	geometry = glCreateShader(GL_GEOMETRY_SHADER);
	glShaderSource(geometry, 1, &gCode, NULL);
	glCompileShader(geometry);
	checkCompileError(geometry, "GEOMETRY");

	glAttachShader(m_ID, geometry);
	glLinkProgram(m_ID);
	checkCompileError(m_ID, "PROGRAM");

	glDeleteShader(geometry);
}

unsigned int Shader::ID() const
{
	return m_ID;
}

void Shader::use()
{
	glUseProgram(m_ID);
}

void Shader::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(m_ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(m_ID, name.c_str()), value);
}

void Shader::setVec2(const std::string& name, const glm::vec2& value) const
{
	glUniform2fv(glGetUniformLocation(m_ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec2(const std::string& name, float x, float y) const
{
	glUniform2f(glGetUniformLocation(m_ID, name.c_str()), x, y);
}

void Shader::setVec3(const std::string& name, const glm::vec3& value) const
{
	glUniform3fv(glGetUniformLocation(m_ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec3(const std::string& name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(m_ID, name.c_str()), x, y, z);
}

void Shader::setVec4(const std::string& name, const glm::vec4& value) const
{
	glUniform4fv(glGetUniformLocation(m_ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec4(const std::string& name, float x, float y, float z, float w) const
{
	glUniform4f(glGetUniformLocation(m_ID, name.c_str()), x, y, z, w);
}

void Shader::setMat2(const std::string& name, const glm::mat2& mat) const
{
	glUniformMatrix2fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat3(const std::string& name, const glm::mat3& mat) const
{
	glUniformMatrix3fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat4(const std::string& name, const glm::mat4& mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::checkCompileError(unsigned int shader, std::string type)
{
	int success;
	char info[1024];
	if (type != "PROGRAME")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, info);
			std::cout << "Error::Shader_Compile_error of type: " << type << "\t" << info << std::endl;
		}
	}
	else
	{
		glGetShaderiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, info);
			std::cout << "Error::Program_Link_error of type: " << type << "\t" << info << std::endl;
		}
	}
}

