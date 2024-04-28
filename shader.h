#pragma once

#include <glad/glad.h>
#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

class Shader {
    private:
        GLuint ID;
    public:
        Shader(const char*, const char*);
        void Use();
};