#include <fluf/drawing/shader.h>
#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <string>

using namespace fluf;

ShaderSource Shader::parse(const String& filepath)
{
	std::ifstream stream(filepath);

	std::string line;
	String vertex_source;
	String fragment_source;
	ShaderType type = ShaderType::NONE;

	while (getline(stream, line))
	{
		if (line.find("@") != std::string::npos)
		{
			if (line.find("vs") != std::string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fs") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else
		{
			if (type == ShaderType::VERTEX)
			{
				vertex_source.append(line.c_str());
				vertex_source.append("\n");
			}
			else if (type == ShaderType::FRAGMENT)
			{
				fragment_source.append(line.c_str());
				fragment_source.append("\n");
			}
		}
	}

	stream.close();

	return { vertex_source, fragment_source };
}

uint Shader::compile(uint type, const String& source)
{
	uint id = glCreateShader(type);
	const char* src = source.cstr();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*) _malloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);

		Log::error("Failed to compile %s shader!", (type == GL_VERTEX_SHADER ? "vertex" : "fragment"));
		Log::info(message);

		glDeleteShader(id);
		return 0;
	}

	return id;
}

Shader::Shader(const String& filepath)
	: m_bound(false)
{
	uint program = glCreateProgram();

	ShaderSource source = Shader::parse(filepath);

	uint vs = Shader::compile(GL_VERTEX_SHADER, source.VertexSource);
	uint fs = Shader::compile(GL_FRAGMENT_SHADER, source.FragmentSource);

	FLUF_ASSERT(vs, "Invalid vertex shader");
	FLUF_ASSERT(fs, "Invalid fragment shader");

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	m_program = program;
}

Shader::~Shader()
{
	glDeleteProgram(m_program);
}

int Shader::uniform_location(const String& name) 
{
	if (m_uniform_location_cache.find(name) != m_uniform_location_cache.end())
		return m_uniform_location_cache[name];

	int location = glGetUniformLocation(m_program, name.cstr());
	if (location == -1)
		Log::warn("uniform '%s' doesn't exist", name.cstr());

	m_uniform_location_cache[name] = location;
	return location;
}

void Shader::set_uniform_1f(const String& name, float v0)
{
	glUniform1f(uniform_location(name), v0);
}

void Shader::set_uniform_1i(const String& name, int v0)
{
	glUniform1i(uniform_location(name), v0);
}

void Shader::set_uniform_2f(const String& name, float v0, float v1)
{
	glUniform2f(uniform_location(name), v0, v1);
}

void Shader::set_uniform_3f(const String& name, float v0, float v1, float v2)
{
	glUniform3f(uniform_location(name), v0, v1, v2);
}

void Shader::set_uniform_4f(const String& name, float v0, float v1, float v2, float v3)
{
	glUniform4f(uniform_location(name), v0, v1, v2, v3);
}

void Shader::set_uniform_mat4(const String& name, const mat4x4& matrix)
{
	glUniformMatrix4fv(uniform_location(name), 1, GL_FALSE, (const GLfloat*)matrix);
}

void Shader::enable()
{
	if (!m_bound)
	{
		glUseProgram(m_program);
		m_bound = true;
	}
}

void Shader::disable()
{
	if (m_bound)
	{
		glUseProgram(0);
		m_bound = false;
	}
}