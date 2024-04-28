#include "shader.h"

Shader::Shader(const char* vertPath, const char* fragPath) {
    string vertCode, fragCode;
    ifstream vertFile, fragFile;

    vertFile.exceptions(ifstream::failbit | ifstream::badbit);
    fragFile.exceptions(ifstream::failbit | ifstream::badbit);

    try {
        vertFile.open(vertPath);
        fragFile.open(fragPath);

        stringstream vertStream, fragStream;
        vertStream << vertFile.rdbuf();
        fragStream << fragFile.rdbuf();

        vertFile.close();
        fragFile.close();

        vertCode = vertStream.str();
        fragCode = fragStream.str();
    }
    catch (ifstream::failure e) {
        cout << "ERROR (FILE): Shader files was not succesfully readed" << endl;
    }

    const char* vertSource = vertCode.c_str();
    const char* fragSource = fragCode.c_str();

    int success;
    char infoLog[512];

    GLuint vertShader, fragShader;
    vertShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertShader, 1, &vertSource, NULL);
    glCompileShader(vertShader);
    glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertShader, 512, NULL, infoLog);
        cout << "ERROR (SHADER): Failed to compile vertex shader\n" << infoLog << endl;
    }

    fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &fragSource, NULL);
    glCompileShader(fragShader);
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
        cout << "ERROR (SHADER): Failed to compile fragment shader\n" << infoLog << endl;
    }

    ID = glCreateProgram();
    glAttachShader(ID, vertShader);
    glAttachShader(ID, fragShader);
    glLinkProgram(ID);
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        cout << "ERROR (SHADER): Failed to link shader program\n\t" << infoLog << endl; 
    }

    glDeleteShader(vertShader);
    glDeleteShader(fragShader);
}

void Shader::Use() {
    glUseProgram(ID);
}