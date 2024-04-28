#version 330 core
layout (location = 0) in vec3 vertCord;
layout (location = 1) in vec3 vertColor;

out vec3 fragColor;

void main() {
    gl_Position = vec4(vertCord, 1.0f);
    fragColor = vertColor;
}