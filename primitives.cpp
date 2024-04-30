#include "primitives.h"
#include <iostream>
#include <memory.h>

void printVec(vec3 v) {
    std::cout << "x: " << v[0] << "\ty: " << v[1] << "\tz: " << v[2] << std::endl;
}

Primitive::Primitive(int num, vec3* shape, vec3* color, vec3 position) {
    commit_transform = mat4(1.0f);
    commit_transform = translate(commit_transform, position);
    transform = commit_transform;
    vertex_num = num;

    vertices = new vec3[num * 2];
    unsigned int k = 0;
    for (int i  = 0; i < num; i++) {
        vertices[k++] = shape[i];
        vertices[k++] = color[i];
    }

    glGenVertexArrays(1, &myVAO);
    glGenBuffers(1, &myVBO);

    glBindVertexArray(myVAO);

    glBindBuffer(GL_ARRAY_BUFFER, myVBO);
    glBufferData(GL_ARRAY_BUFFER, 2 * num * sizeof(vec3), vertices, GL_STATIC_DRAW);
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

    glDeleteBuffers(1, &myVBO);
    glDeleteVertexArrays(1, &myVAO);
}

mat4* Primitive::GetTransform() {
    return &transform;
}

void Primitive::Translate(vec3 pos) {
    UpdateTransform();
    transform = translate(transform, pos);
}

void Primitive::Rotate(float angle, vec3 axis) {
    UpdateTransform();
    transform = rotate(transform, angle, axis);
}

void Primitive::UpdateTransform() {
    transform = commit_transform;
}

void Primitive::CommitTransform() {
    commit_transform = transform;
}

void Primitive::Draw() {
    glBindVertexArray(myVAO);
    glDrawArrays(GL_TRIANGLES, 0, vertex_num);
}



Triangle::Triangle(vec3 pos, vec3* col) {
    memcpy(color, col, 3 * sizeof(vec3));
    commit_transform = mat4(1.0f);
    commit_transform = translate(commit_transform, pos);
    transform = commit_transform;

    unsigned int k = 0;
    for (int i  = 0; i < 3; i++) {
        vertices[k++] = cords[i];
        vertices[k++] = color[i];
    }

    glGenVertexArrays(1, &myVAO);
    glGenBuffers(1, &myVBO);

    glBindVertexArray(myVAO);

    glBindBuffer(GL_ARRAY_BUFFER, myVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}


Triangle::~Triangle() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glDeleteBuffers(1, &myVBO);
    glDeleteVertexArrays(1, &myVAO);
}

mat4* Triangle::GetTransform() {
    return &transform;
}

void Triangle::UpdateTransform() {
    transform = commit_transform;
}

void Triangle::CommitTransform() {
    commit_transform = transform;
}

void Triangle::Translate(vec3 pos) {
    UpdateTransform();
    transform = translate(transform, pos);
}

void Triangle::Rotate(float angle, vec3 axis) {
    UpdateTransform();
    transform = rotate(transform, angle, axis);
}

void Triangle::Draw() {
    glBindVertexArray(myVAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}