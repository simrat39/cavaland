//
// Created by simrat39 on 12/29/23.
//

#pragma once

#include "Shader.hpp"
#include <epoxy/gl.h>
#include <epoxy/gl_generated.h>

class Renderer {
public:
  Renderer();

  void pre_render();
  void render(float *data);
private:
  GLuint VAO;
  GLuint VBO;
  GLuint EBO;

  GLfloat width;
  GLfloat height;
  GLuint bars;

  Shader *shader;
};
