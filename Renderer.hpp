//
// Created by simrat39 on 12/29/23.
//

#pragma once

#include <epoxy/gl.h>
#include <glm/glm.hpp>
#include "Shader.hpp"

class Renderer {
public:
   void pre_render();
   void render(float* data);
private:
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;

    Shader* shader;
};
