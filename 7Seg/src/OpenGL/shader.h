#pragma once
#include <string>
#include <unordered_map>

struct ShaderProgramSource
{
	std::string vertexSource;
	std::string fragmentSource;
};

class Shader
{
private:
	std::string m_FilePath;
	unsigned int m_RendererID;
	
	//caching for uniforms
	std::unordered_map<std::string, int> m_UniformLocationCache;
public:
	Shader(const std::string& filepath);
	Shader();
	~Shader();

	void bind() const;
	void unbind() const;
	void addShader(const std::string& filepath);
	void addPBShader(const std::string& PBShader);

	//set uniforms
	void setUniform1f(const std::string& name, float value);
	void setUniform1i(const std::string& name, int value); 
	void setUniform4f(const std::string& name, float f0, float f1, float f2, float f3);

private:
	unsigned int compileShader(unsigned int type, const std::string& source);
	unsigned int createShader(const std::string& vertShader, const std::string& fragShader);
	ShaderProgramSource parseShader(const std::string& filepath);
	ShaderProgramSource parseBuiltShader(const std::string& filepath);

	int getUniformLocation(const std::string& name);
};
