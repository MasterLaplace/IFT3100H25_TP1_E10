#ifndef SHADERLOADER_HPP
#define SHADERLOADER_HPP

#include <GL/glew.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

class ShaderLoader {
public:
    static GLuint LoadShader(const char *path, GLenum type)
    {
        std::ifstream file(path);
        if (!file.is_open())
        {
            std::cerr << "Erreur: Impossible de charger le shader " << path << std::endl;
            return 0;
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string source = buffer.str();
        const char *source_cstr = source.c_str();

        GLuint shader = glCreateShader(type);
        glShaderSource(shader, 1, &source_cstr, nullptr);
        glCompileShader(shader);

        int success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            char infoLog[512];
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);
            std::cerr << "Erreur de compilation du shader (" << path << "):\n" << infoLog << std::endl;
        }

        return shader;
    }
};

#endif // SHADERLOADER_HPP
