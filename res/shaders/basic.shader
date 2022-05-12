@vs
#version 330 core

layout(location = 0) in vec4 position;
#layout(location = 1) in vec4 color;
uniform mat4 pr_matrix;
uniform mat4 ml_matrix = mat4(1.0);

out DATA
{
	vec4 position;
	vec4 color;
} vs_out;

void main()
{
	gl_Position = pr_matrix * ml_matrix * position;
	vs_out.position = ml_matrix * position;
	#vs_out.color = color;
}

@fs
#version 330 core
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) out vec4 color;
uniform vec2 light_pos;

in DATA
{
	vec4 position;
	vec4 color;
} fs_in;

void main()
{
	float intensity = 1.0 / length(fs_in.position.xy - light_pos);
	color = fs_in.color * intensity;
}