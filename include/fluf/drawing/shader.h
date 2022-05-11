#pragma once
#include <fluf/common.h>
#include <fluf/math/spatial.h>
#include <string>

namespace Fluf
{
	class Shader
	{
	private:
		uint m_program;
		
		static uint compile(uint type, const std::string& source);

	public:
		Shader(const std::string& vertex, const std::string& fragment);
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