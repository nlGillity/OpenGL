#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "shader.h"
#include "primitives.h"
#include <vector>
#include <iostream>
using namespace glm;
using namespace std;

#define BLACK vec3(0.0f, 0.0f, 0.0f)
#define WHITE vec3(1.0f, 1.0f, 1.0f)
#define   RED vec3(1.0f, 0.0f, 0.0f)
#define  BLUE vec3(0.0f, 1.0f, 0.0f)
#define GREEN vec3(0.0f, 0.0f, 0.0f) 

const int WIDTH  = 800;
const int HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow*, int, int);
void key_callback(GLFWwindow*, int, int, int, int);

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_COMPAT_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "App", NULL ,NULL);
    if (window == NULL) {
        cout << "ERROR: Failed to create a window" << endl;
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cout << "ERROR: Falied to init GLAD" << endl;
        glfwTerminate();
        return 1;
    }

    Shader myShader("shaders/vertex.vert", "shaders/fragment.frag");

    vec3* triangle_color = new vec3[3] {
        vec3(1.0, 0.0, 0.0),
        vec3(0.0, 1.0, 0.0),
        vec3(0.0, 0.0, 1.0)
    };

    Triangle myTriangle(triangle_color, vec3(0.0, 0.0, 0.0));

    myShader.Use();
    while(!glfwWindowShouldClose(window)) {
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        myTriangle.Rotate((float)glfwGetTime(), vec3(0.0f, 1.0f, 0.0f));
        myShader.SetUniformMat("trans", *myTriangle.GetTransform());
        myShader.SetUniform("time", (float)glfwGetTime());

        myTriangle.Draw();

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scanmode, int actions, int mods) {
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}