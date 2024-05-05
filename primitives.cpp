#include "primitives.h"
#include <iostream>
#include <memory.h>

void printVec(vec3 v) {
    std::cout << "x: " << v[0] << "\ty: " << v[1] << "\tz: " << v[2] << std::endl;
}

Primitive::Primitive(int num, vec3* shape, vec3* color, vec3 position) : number_vertices(num) {
    buildVertexData(shape, color);
    createVAO();

    static_transform = mat4(1.0f);
    static_transform = translate(static_transform, position);
    dynamic_transform = static_transform;
}

Primitive::Primitive(int num, vec3* shape, unsigned int* inds, vec3* color, vec3 position) : number_vertices(num) {
    buildVertexData(shape, inds, color);
    createVAO();

    static_transform = mat4(1.0f);
    static_transform = translate(static_transform, position);
    dynamic_transform = static_transform;
}   

void Primitive::buildVertexData(vec3* shape, vec3* color) {
    vertices = new vec3[2 * number_vertices];
    unsigned int k = 0;
    for (int i  = 0; i < number_vertices; i++) {
        vertices[k++] = shape[i];
        vertices[k++] = color[i];
    }

    indices = new unsigned int[number_vertices];
    for (int i = 0; i < number_vertices; i++)
        indices[i] = i;
}

void Primitive::buildVertexData(vec3* shape, unsigned int* inds, vec3* color) {
    vertices = new vec3[2 * number_vertices];
    unsigned int k = 0;
    for (int i  = 0; i < number_vertices; i++) {
        vertices[k++] = shape[i];
        vertices[k++] = color[i];
    }

    indices = new unsigned int[number_vertices];
    for (int i = 0; i < number_vertices; i++) {
        indices[i] = inds[i];
    }
}

void Primitive::createVAO() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 2 * number_vertices * sizeof(vec3), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, number_vertices * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Primitive::~Primitive() {
    delete [] vertices;

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glDeleteBuffers(1, &EBO);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}

mat4* Primitive::GetTransform() {
    return &dynamic_transform;
}

void Primitive::Translate(vec3 pos) {
    UpdateTransform();
    dynamic_transform = translate(dynamic_transform, pos);
}

void Primitive::Rotate(float angle, vec3 axis) {
    UpdateTransform();
    dynamic_transform = rotate(dynamic_transform, angle, axis);
}

void Primitive::UpdateTransform() {
    dynamic_transform = static_transform;
}

void Primitive::CommitTransform() {
    static_transform = dynamic_transform;
}

void Primitive::Draw() {
    glBindVertexArray(VAO);
    //glDrawArrays(GL_TRIANGLES, 0, number_vertices);
    glDrawElements(GL_TRIANGLES, number_vertices, GL_UNSIGNED_INT, 0);
}