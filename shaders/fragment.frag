#version 330 core

uniform float time;

in vec3 fragColor;
out vec4 color;

void main() {
    vec3 res = abs(sin(fragColor + time));
    color = vec4(res, 1.0f);
}