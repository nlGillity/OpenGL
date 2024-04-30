#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace std;
using namespace glm;

class Primitive {
private:
    unsigned int number_vertices;
    unsigned int* indices;
    vec3* vertices;
    GLuint VAO, VBO, EBO;
    mat4 static_transform, dynamic_transform;

    void buildVertexData(vec3* shape, vec3* color);
    void buildVertexData(vec3* shape, unsigned int* indices,vec3* color);
    void createVAO();

public:
    Primitive(int num, vec3* shape, vec3* color, vec3 position);
    Primitive(int num, vec3* shape, unsigned int* indices, vec3* color, vec3 position);
    ~Primitive();

    mat4* GetTransform();
    void Translate(vec3 position);
    void Rotate(float angle, vec3 axix);

    void UpdateTransform();
    void CommitTransform();

    void Draw();
};

class Triangle: public Primitive {
    private:
    public:
        Triangle(vec3* color, vec3 position) : 
        Primitive(3, new vec3[3]{
            vec3(-0.5, -0.5, 0.0),
            vec3( 0.5, -0.5, 0.0),
            vec3( 0.0,  0.5, 0.0)},
        color, position) {}
};

#endif