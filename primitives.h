#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

class Triangle {
private:
    vec3 cords[3] = {
        vec3(-0.5f, -0.5f, 0.0f),
        vec3( 0.5f, -0.5f, 0.0f),
        vec3( 0.0f,  0.5f, 0.0f)
    };
    vec3 vertices[6];
    GLuint myVAO, myVBO;

public:
    vec3 color[3];
    mat4 transform;

    Triangle(vec3, vec3*);
    ~Triangle();

    void Translate(vec3);
    void Draw();
};