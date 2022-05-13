@vs
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 tex_coord;

out vec2 v_tex_coord;

void main()
{
	gl_Position = position;
	v_tex_coord = tex_coord;
}

@fs
#version 330 core

out vec4 color;

in vec2 v_tex_coord;

uniform vec4 u_color;
uniform sampler2D u_tex;

void main()
{
	vec4 tex_color = texture(u_tex, v_tex_coord);
	color = tex_color;
}