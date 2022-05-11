#include <fluf/drawing/shader.h>
#include <GL/glew.h>

using namespace Fluf;

uint Shader::compile(uint type, const std::string& source)
{
	uint id = glCreateShader(type);
	const char* src = source.c_str();
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

Shader::Shader(const std::string& vertex, const std::string& fragment)
{
	uint program = glCreateProgram();

	uint vs = Shader::compile(GL_VERTEX_SHADER, vertex);
	uint fs = Shader::compile(GL_FRAGMENT_SHADER, fragment);

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

int Shader::uniform_location(const char* name) const
{
	return glGetUniformLocation(m_program, name);
}

void Shader::set_uniform_1f(const char* name, float value) const
{
	glUniform1f(uniform_location(name), value);
}

void Shader::set_uniform_2f(const char* name, const vec2& vector) const
{
	glUniform2f(uniform_location(name), vector[0], vector[1]);
}

void Shader::set_uniform_3f(const char* name, const vec3& vector) const
{
	glUniform3f(uniform_location(name), vector[0], vector[1], vector[2]);
}

void Shader::set_uniform_4f(const char* name, const vec4& vector) const
{
	glUniform4f(uniform_location(name), vector[0], vector[1], vector[2], vector[3]);
}

void Shader::set_uniform_mat4(const char* name, const mat4x4& matrix) const
{
	glUniformMatrix4fv(uniform_location(name), 1, GL_FALSE, (const GLfloat*)matrix);
}

void Shader::enable() const
{
	glUseProgram(m_program);
}

void Shader::disable() const
{
	glUseProgram(0);
}