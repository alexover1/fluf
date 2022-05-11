#pragma once
#include <fluf/common.h>
#include <fluf/containers/str.h>
#include <fluf/math/spatial.h>
#include <string>

namespace Fluf
{
	enum class ShaderType
	{
		NONE = -1,
		VERTEX = 0,
		FRAGMENT = 1
	};

	struct ShaderSource
	{
		String VertexSource;
		String FragmentSource;
	};

	class Shader
	{
	private:
		uint m_program;
		
		static ShaderSource parse(const String& filepath);
		static uint compile(uint type, const String& source);

	public:
		Shader(const String& filepath);
		~Shader();


		int uniform_location(const char* name) const;
		void set_uniform_1f(const char* name, float value) const;
		void set_uniform_2f(const char* name, const vec2& value) const;
		void set_uniform_3f(const char* name, const vec3& value) const;
		void set_uniform_4f(const char* name, const vec4& value) const;
		void set_uniform_mat4(const char* name, const mat4x4& matrix) const;

		void enable() const;
		void disable() const;
	};
}