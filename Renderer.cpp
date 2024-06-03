//
// Created by simrat39 on 12/29/23.
//

#include "Renderer.hpp"
#include "ConfigManager.hpp"
#include "constants.hpp"
#include <epoxy/gl.h>
#include <vector>
#include <string>

void Renderer::pre_render()
{
  shader = new Shader{
      "/usr/share/cavaland/shaders/vertex.glsl",
      ConfigManager::get_instance()
          .get_or_default<std::string>("shader",
                                       "/usr/share/cavaland/shaders/bars/x_gradient.glsl")
          .c_str(),
  };

  // Pre Draw
  std::vector<GLfloat> vertices = {
      // x   y       z
      RIGHT, TOP, 0.f,    // top right
      RIGHT, BOTTOM, 0.f, // bottom right
      LEFT, BOTTOM, 0.f,  // bottom left
      LEFT, TOP, 0.f      // top left
  };

  std::vector<GLuint> indices = {0, 1, 3, 1, 2, 3};

  // VAO
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  // VBO
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat),
               vertices.data(), GL_STATIC_DRAW);

  // EBO
  // This is after VAO cuz it needs the VAO
  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint),
               indices.data(), GL_STATIC_DRAW);

  // This is after VBO cuz it needs the VBO
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);
  glEnableVertexAttribArray(0);

  shader->register_uniform("heights");
  shader->register_uniform("width");
  shader->register_uniform("height");
  shader->register_uniform("num_bars");

  glViewport(0, 0, WIDTH, HEIGHT);
}

void Renderer::render(float *data)
{
  glClear(GL_COLOR_BUFFER_BIT);

  shader->use();

  auto &cfg = ConfigManager::get_instance();

  shader->set_float_uniform("width", cfg.get_or_default<float>("width", 1920));
  shader->set_float_uniform("height", cfg.get_or_default<float>("height", 200));
  shader->set_float_uniform("num_bars", cfg.get_or_default<float>("bars", 120));
  // Maybe use a texture for this
  shader->set_float_array_uniform("heights", NUM_BARS, data);

  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, 8, GL_UNSIGNED_INT, nullptr);
}
