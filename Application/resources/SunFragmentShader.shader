#version 330 core

layout(location = 0) out vec4 color;

in vec3 Normal;
in vec3 FragPos;

void main() {
	color = vec4(1.0);
};