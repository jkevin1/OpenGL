#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Shader {
    GLuint id;
public:
    Shader(const char* vert, const char* frag);
    virtual ~Shader();

    void use();
    GLuint getUniform(const char* name);
};

#endif //SHADER_H
