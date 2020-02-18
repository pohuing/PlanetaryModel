#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

out vec3 FragPos;
out vec3 Normal;

uniform mat4 ModelMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 ViewMatrix;

void main()
{
	FragPos = vec3(ModelMatrix * vec4(position, 1.0));
	Normal = mat3(transpose(inverse(ModelMatrix))) * normal;

	gl_Position = ProjectionMatrix * ViewMatrix  * vec4(FragPos, 1.0);
}
