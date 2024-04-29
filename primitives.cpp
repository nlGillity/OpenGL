#include "primitives.h"
#include <memory.h>

Triangle::Triangle(vec3 pos, vec3* col) {
    memcpy(color, col, 3 * sizeof(vec3));
    transform = mat4(0.0f);
    transform = translate(transform, pos);

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
    glDeleteBuffers(1, &myVBO);
    glDeleteVertexArrays(1, &myVAO);
}

void Triangle::Translate(vec3 trans) {
    transform = translate(transform, trans);
}

void Triangle::Draw() {
    glBindVertexArray(myVAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}