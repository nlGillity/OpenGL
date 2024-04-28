#pragma once

#include <glm/glm.hpp>

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

        template <typename T>
        void SetUniform(const char* name, T value) {
            GLuint location = glGetUniformLocation(ID, name);
            string tName = typeid(value).name();
    
            if (tName == typeid(GLuint).name())
                glUniform1ui(location, value);
            else if (tName == typeid(GLint).name())
                glUniform1i(location, value);
            else if (tName == typeid(GLfloat).name())
                glUniform1f(location, value);
            else
                cout << "ERROR (UNIFORM): Failed to recognize uniform type" << endl;
        }

        template <typename T>
        void SetUniformVec(const char* name, T &value) {
            GLuint location = glGetUniformLocation(ID, name);
            string tName = typeid(value).name();
    
            if (tName == typeid(glm::vec2).name())
                glUniform2fv(location, 1, &value[0]);
            else if (tName == typeid(glm::vec3).name())
                glUniform3fv(location, 1, &value[0]);
            else if (tName == typeid(glm::vec4).name())
                glUniform4fv(location, 1, &value[0]);
            else
                cout << "ERROR (UNIFORM): Failed to recognize uniform vec type" << endl;
        }

        template <typename T>
        void SetUniformMat(const char* name, T &value) {
            GLuint location = glGetUniformLocation(ID, name);
            string tName = typeid(value).name();
    
            if (tName == typeid(glm::mat2).name())
                glUniformMatrix2fv(location, 1, GL_FALSE, &value[0][0]);
            else if (tName == typeid(glm::mat3).name())
                glUniformMatrix3fv(location, 1, GL_FALSE, &value[0][0]);
            else if (tName == typeid(glm::mat4).name())
                glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
            else
                cout << "ERROR (UNIFORM): Failed to recognize uniform mat type" << endl;
        }

};