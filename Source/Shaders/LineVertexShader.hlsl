#version 330 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aColor;

uniform mat4 uProjection;
uniform mat4 uView;

out vec3 vColor;

void main()
{
	gl_Position = uProjection * uView * vec4(aPosition, 1.0);
	vColor = aColor;
}