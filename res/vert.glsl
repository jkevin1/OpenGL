#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 worldPos;
out vec3 worldNorm;

void main() {
	worldPos = mat3(model) * position;
	worldNorm = normalize(mat3(model) * normal);
	gl_Position = projection * view * model * vec4(position, 1.0);
}
