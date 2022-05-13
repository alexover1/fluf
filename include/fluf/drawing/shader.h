#pragma once
#include <fluf/common.h>
#include <fluf/linmath.h>
#include <fluf/containers/str.h>
#include <fluf/containers/vector.h>
#include "renderer.h"
#include <unordered_map>

namespace fluf
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
		bool m_bound;
		std::unordered_map<String, int> m_uniform_location_cache;
		
		static ShaderSource parse(const String& filepath);
		static uint compile(uint type, const String& source);

	public:
		Shader(const String& filepath);
		~Shader();

		int uniform_location(const String& name);
		void set_uniform_1f(const String& name, float v0);
		void set_uniform_1i(const String& name, int v0);
		void set_uniform_2f(const String& name, float v0, float v1);
		void set_uniform_3f(const String& name, float v0, float v1, float v2);
		void set_uniform_4f(const String& name, float v0, float v1, float v2, float v3);
		void set_uniform_mat4(const String& name, const mat4x4& matrix);

		void enable();
		void disable();
	};
}