//
// Created by simrat39 on 12/28/23.
//

#pragma once

#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>
#include <epoxy/gl.h>

class Shader {
public:
    GLuint ID;
    std::unordered_map<std::string, GLuint> uniforms;

    Shader(const char* vertex_shader_src_file, const char* fragment_shader_src_file) {
        std::ifstream vertex_fstream{vertex_shader_src_file};
        std::stringstream vertex_sstream;
        vertex_sstream << vertex_fstream.rdbuf();
        vertex_fstream.close();

        std::ifstream fragment_fstream{fragment_shader_src_file};
        std::stringstream fragment_sstream;
        fragment_sstream << fragment_fstream.rdbuf();
        fragment_fstream.close();

        std::string vertex_src_str = vertex_sstream.str();
        std::string fragment_src_str = fragment_sstream.str();

        const char* vertex_src = vertex_src_str.c_str();
        const char* fragment_src = fragment_src_str.c_str();

        int success;
        char infoLog[512];

        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertex_src, nullptr);
        glCompileShader(vertexShader);
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
            std::cout << "Error: vertex shader couldn;t compile: " << infoLog << std::endl;
        }

        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragment_src, nullptr);
        glCompileShader(fragmentShader);
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
            std::cout << "Error: fragment shader couldn;t compile: " << infoLog << std::endl;
        }

        ID = glCreateProgram();
        glAttachShader(ID, vertexShader);
        glAttachShader(ID, fragmentShader);
        glLinkProgram(ID);

        // check for linking errors
        glGetProgramiv(ID, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(ID, 512, nullptr, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }

        // Deleting cuz we linked to the shader program already
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    void use() {
        glUseProgram(ID);
    }

    void register_uniform(std::string key) {
        uniforms[key] = glGetUniformLocation(ID, key.c_str());
    }

    void set_float_array_uniform(std::string key, GLint count, float value[]) {
        GLuint location = uniforms.at(key);
        glUniform1fv(location, count, value);
    }

    void set_float_uniform(std::string key, float value) {
        GLuint location = uniforms.at(key);
        glUniform1f(location, value);
    }
};

