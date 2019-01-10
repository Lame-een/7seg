#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "shader.h"
#include "renderer.h"

Shader::Shader(const std::string& filepath)
	: m_FilePath(filepath), m_RendererID(0)
{
	ShaderProgramSource source = parseShader(filepath);
	m_RendererID = createShader(source.vertexSource, source.fragmentSource);
}

Shader::Shader()
	: m_RendererID(0)
{
}

void Shader::addShader(const std::string& filepath)
{
	m_FilePath = filepath;
	ShaderProgramSource source = parseShader(filepath);
	m_RendererID = createShader(source.vertexSource, source.fragmentSource);
}

void Shader::addPBShader(const std::string& PBShader)
{
	ShaderProgramSource source = parseBuiltShader(PBShader);
	m_RendererID = createShader(source.vertexSource, source.fragmentSource);
}

Shader::~Shader()
{
	GLCall(glDeleteProgram(m_RendererID));
}

ShaderProgramSource Shader::parseBuiltShader(const std::string& shaderSource)
{
	std::stringstream stream(shaderSource);

	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;
	while(getline(stream, line))
	{
		if(line.find("#shader") != std::string::npos)
		{
			if(line.find("vertex") != std::string::npos)
			{
				type = ShaderType::VERTEX;
			}
			else if(line.find("fragment") != std::string::npos)
			{
				type = ShaderType::FRAGMENT;
			}
		}
		else
		{
			ss[(int)type] << line << '\n';
		}
	}

	return {ss[0].str(), ss[1].str()};
}

ShaderProgramSource Shader::parseShader(const std::string& filepath)
{
	std::ifstream stream(filepath);

	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;
	while(getline(stream, line))
	{
		if(line.find("#shader") != std::string::npos)
		{
			if(line.find("vertex") != std::string::npos)
			{
				type = ShaderType::VERTEX;
			}
			else if(line.find("fragment") != std::string::npos)
			{
				type = ShaderType::FRAGMENT;
			}
		}
		else
		{
			ss[(int)type] << line << '\n';
		}
	}

	return {ss[0].str(), ss[1].str()};
}

unsigned int Shader::compileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);    //docu
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);    //docu
	glCompileShader(id);    //docu

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);    //docu
	if(result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile" << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader" << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);

		return 0;
	}

	return id;
}

unsigned int Shader::createShader(const std::string& vertShader, const std::string& fragShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = compileShader(GL_VERTEX_SHADER, vertShader);
	unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragShader);

	glAttachShader(program, vs);    //docu
	glAttachShader(program, fs);    //docu
	glLinkProgram(program);    //docu
	glValidateProgram(program);    //docu

	glDeleteShader(vs);    //docu
	glDeleteShader(fs);    //docu

	return program;
}



void Shader::bind() const
{
	GLCall(glUseProgram(m_RendererID));
}

void Shader::unbind() const
{
	GLCall(glUseProgram(0));
}

void Shader::setUniform4f(const std::string& name, float f0, float f1, float f2, float f3)
{
	GLCall(glUniform4f(getUniformLocation(name), f0, f1, f2, f3));
}

void Shader::setUniform1f(const std::string& name, float value)
{
	GLCall(glUniform1f(getUniformLocation(name), value));
}

void Shader::setUniform1i(const std::string& name, int value)
{
	GLCall(glUniform1i(getUniformLocation(name), value));
}

int Shader::getUniformLocation(const std::string& name)
{
	if(m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
	{
		return m_UniformLocationCache[name];
	}

	GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));

	if(location == -1)
	{
		std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;
	}

	m_UniformLocationCache[name] = location;

	return location;
}
