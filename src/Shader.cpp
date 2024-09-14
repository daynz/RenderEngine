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

