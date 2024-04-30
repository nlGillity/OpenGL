#pragma once
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace std;
using namespace glm;

class Primitive {
private:
    unsigned int vertex_num;
    vec3* vertices;
    GLuint myVAO, myVBO;

    mat4 transform, commit_transform;
public:
    Primitive(int num, vec3* shape, vec3* color, vec3 position);
    ~Primitive();

    mat4* GetTransform();
    void Translate(vec3 position);
    void Rotate(float angle, vec3 axix);

    void UpdateTransform();
    void CommitTransform();

    void Draw();
};

class Triangle {
private:
    vec3 cords[3] = {
        vec3(-0.5f, -0.5f, 0.0f),
        vec3( 0.5f, -0.5f, 0.0f),
        vec3( 0.0f,  0.5f, 0.0f)
    };
    vec3 vertices[6];
    GLuint myVAO, myVBO;
    mat4 commit_transform;

public:
    vec3 color[3];
    mat4 transform;

    Triangle(vec3, vec3*);
    ~Triangle();

    mat4* GetTransform();

    void UpdateTransform();
    void CommitTransform();
    void Translate(vec3 position);
    void Rotate(float angle, vec3 axix);
    void Draw();
};