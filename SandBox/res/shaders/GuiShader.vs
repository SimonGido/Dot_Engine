#version 330 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec4 color;

out vec4 color0;

uniform vec2 transform;
uniform mat4 mvp;


void main()
{
	gl_Position = mvp * vec4(position,0.0,1.0);

	color0 = color;
		
}