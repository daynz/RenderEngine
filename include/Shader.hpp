#pragma once

#include <string>

class Shader
{
public:
	Shader(std::string vertexPath, std::string fragmentPath);
	Shader(std::string vertexPath, std::string fragmentPath, std::string geometryPath);

	unsigned int ID()const;

	void use();

private:
	void checkCompileError(unsigned int shader,std::string type);

	unsigned int m_ID;
};