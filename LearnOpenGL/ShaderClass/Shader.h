#pragma

#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
private:
	void checkCompileErrors(unsigned int shader, std::string type);
public:
	unsigned int id;//程序id

	Shader(const char* vertexPath, const char* fragmentPath);

	//使用程序
	void useProgram();
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
};

#endif

