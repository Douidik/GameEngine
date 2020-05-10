#pragma once
#include "Texture.h"

enum ShaderType
{
	Vertex = 0x8B31,
	Fragment = 0x8B30,
	None = 0
};

#define NULL_SHADER 0xfffffff

class Shader
{
public:
	Shader(const std::string& fpVertex, const std::string& fpFragment);
	inline void bind() const { glUseProgram(mId); }
	inline static void UnBind() { glUseProgram(0); }

private:
	std::tuple<std::string, std::string> readShader(std::tuple<std::string, std::string> filepaths);
	GLuint parseProgram(std::tuple<std::string, std::string> sources);
	GLuint parseShader(const std::string& source, ShaderType type);

private:
	GLuint mId;

private:
	std::unordered_map<std::string, int> mLayoutLocationCache;

public:
	int getLayoutLocation(const std::string& name);

private:
	std::unordered_map<std::string, int> mUniformLocationCache;

public:
    void setUniform(const std::string &name, int value);
    void setUniform(const std::string &name, unsigned int value);
    void setUniform(const std::string &name, float value);
    void setUniform(const std::string& name, double value);
    void setUniform(const std::string &name, glm::vec2 value);
    void setUniform(const std::string &name, glm::vec3 value);
    void setUniform(const std::string &name, glm::vec4 value);
    void setUniform(const std::string &name, glm::mat3 value);
    void setUniform(const std::string &name, glm::mat4 value);

	void setTexture(Texture* texture)
	{
		texture->bind();
		setUniform(texture->getUniformName(), texture->getSlot());
	}
	
private:
	GLuint getUniformLocation(const std::string& name)
	{
		if (mUniformLocationCache.find(name) != mUniformLocationCache.end())
		{
			return mUniformLocationCache[name];
		}

		GLuint location = glGetUniformLocation(mId, name.c_str());

		if (location == -1)
		{
			std::string errorMessage = "Failed to find uniform location: " + name;
			std::cerr << errorMessage << std::endl;
		}

		mUniformLocationCache[name] = location;

		return location;
	}

};


