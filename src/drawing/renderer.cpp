#include <fluf/drawing/renderer.h>
#include <fluf/drawing/shader.h>
#include <fluf/drawing/varray.h>
#include <fluf/drawing/ibuffer.h>
#include <glad/glad.h>

using namespace fluf;

namespace
{
	const char* shader_source = R""""(
		@vs
		#version 330 
		
		layout(location = 0) in vec4 position;

		void main()
		{
			gl_Position = position;
		}

		@fs
		#version 330 core
		#extension GL_ARB_separate_shader_objects : enable

		layout(location = 0) out vec4 color;

		void main()
		{
			color = vec4(1.0, 0.0, 0.0, 1.0);
		}
	)"""";
}

void Renderer::draw_triangles(const varray& va, const ibuffer& ib, const Shader& shader) const
{
	shader.enable();
	va.bind();
	ib.bind();
	
	glDrawElements(GL_TRIANGLES, ib.count(), GL_UNSIGNED_SHORT, nullptr);
}