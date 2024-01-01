//
// Created by simrat39 on 12/29/23.
//

#include "Renderer.hpp"
#include <epoxy/gl.h>
#include <vector>

void Renderer::pre_render() {
    shader = new Shader{"../shaders/vertex.glsl", "../shaders/bars/x_gradient.glsl"};

    // Pre Draw
    std::vector<GLfloat> vertices = {
            // x   y       z
            RIGHT, TOP   , 0.f,  // top right
            RIGHT, BOTTOM, 0.f,   // bottom right
            LEFT , BOTTOM, 0.f,   // bottom left
            LEFT , TOP   , 0.f   // top left
    };

    std::vector<GLuint> indices = {
            0, 1, 3,
            1, 2, 3
    };

    // VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // VBO
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

    // EBO
    // This is after VAO cuz it needs the VAO
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    // This is after VBO cuz it needs the VBO
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);
    glEnableVertexAttribArray(0);

    shader->register_uniform("heights");
    shader->register_uniform("width");
    shader->register_uniform("height");

    glViewport(0,0, WIDTH, HEIGHT);
}

void Renderer::render(float *data) {
    glClear(GL_COLOR_BUFFER_BIT);

    shader->use();

    shader->set_float_uniform("width", WIDTH);
    shader->set_float_uniform("height", HEIGHT);
    shader->set_float_array_uniform("heights", NUM_BARS, data);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 8, GL_UNSIGNED_INT, (void*)0);
}
