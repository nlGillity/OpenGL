#version 330 core
layout (location = 0) in vec3 vertCord;
layout (location = 1) in vec3 vertColor;

uniform mat4 trans;
out vec3 fragColor;

void main() {
    gl_Position = trans * vec4(vertCord, 1.0f);
    fragColor = vertColor;
}