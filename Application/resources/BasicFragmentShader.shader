#version 330 core

layout(location = 0) out vec4 color;

uniform float AmbientLightIntensity;
uniform vec4 AmbientLightColor;


in vec4 FragColor;

void main()
{
	color = FragColor;
};