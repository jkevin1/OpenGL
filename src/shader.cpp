#include <string>
#include <fstream>
//#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include "shader.h"

GLuint loadShader(const char* filename, GLenum type) {
    printf("Loading shader: %s\n", filename);
    //open the file and calculate the length of the file
	std::string content;
	std::ifstream fileStream(filename, std::ios::in);

	if (!fileStream.is_open()) {
		fprintf(stderr, "Failed to open file\n");
	}

	std::string line = "";
	while (!fileStream.eof()) {
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();

    //create and compile the shader
    GLuint id = glCreateShader(type);
	const char* src = content.c_str();
    glShaderSource(id, 1, &src, NULL);
    glCompileShader(id);

    GLint compiled;
    glGetShaderiv(id, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
        GLint error_len;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &error_len);
        char* error = (char*)malloc(error_len);
        glGetShaderInfoLog(id, error_len, NULL, error);
        printf(error);
        free(error);
    }

    return id;
}

Shader::Shader(const char* vert, const char* frag) {
    GLuint vertID = loadShader(vert, GL_VERTEX_SHADER);
    GLuint fragID = loadShader(frag, GL_FRAGMENT_SHADER);

    id = glCreateProgram();
    glAttachShader(id, vertID);
    glAttachShader(id, fragID);
    glLinkProgram(id);

    GLint linked;
    glGetProgramiv(id, GL_LINK_STATUS, &linked);
    if (!linked) {
        GLint error_len;
        glGetProgramiv(id, GL_INFO_LOG_LENGTH, &error_len);
        char* error = (char*)malloc(error_len);
        glGetProgramInfoLog(id, error_len, NULL, error);
        printf(error);
        free(error);
    }

    glDeleteShader(vertID);
    glDeleteShader(fragID);
}

Shader::~Shader() {
    glDeleteProgram(id);
}

void Shader::use() {
    glUseProgram(id);
}

GLuint Shader::getUniform(const char* name) {
    return glGetUniformLocation(id, name);
}
