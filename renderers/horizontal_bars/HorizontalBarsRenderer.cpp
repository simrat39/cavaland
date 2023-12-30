//
// Created by simrat39 on 12/29/23.
//

#include "HorizontalBarsRenderer.hpp"
#include <epoxy/gl.h>
#include <vector>

void HorizontalBarsRenderer::pre_render() {
    shader = new Shader{"../shaders/bars/vertex.glsl", "../shaders/bars/fragment.glsl"};

    float bar_width = (2.f/NUM_BARS);

    // Pre Draw
    std::vector<GLfloat> vertices = {
            // x              y                              z
            LEFT + bar_width, BOTTOM + INITIAL_BAR_HEIGHT  , 0.0f,  // top right
            LEFT + bar_width, BOTTOM                       , 0.f,   // bottom right
            LEFT            , BOTTOM                       , 0.f,   // bottom left
            LEFT            , BOTTOM + INITIAL_BAR_HEIGHT  , 0.0f   // top left
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

    for (int i = 0; i < NUM_BARS; ++i) {
        offsets[i] = glm::vec2{i * (bar_width), 0};
    }

    // OFFSET_VBO
    glGenBuffers(1, &OFFSET_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, OFFSET_VBO);
    glBufferData(GL_ARRAY_BUFFER, offsets.size() * sizeof(glm::vec2), offsets.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glVertexAttribDivisor(1, 1);
    glEnableVertexAttribArray(1);
}

void HorizontalBarsRenderer::render(float* data) {
    glClear(GL_COLOR_BUFFER_BIT);

    shader->use();

    for (int i = 0; i < NUM_BARS; ++i) {
        offsets[i].y = data[i];
    }
    glBufferData(GL_ARRAY_BUFFER, offsets.size() * sizeof(glm::vec2), offsets.data(), GL_STATIC_DRAW);

    glBindVertexArray(VAO);
    glDrawElementsInstanced(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0, NUM_BARS);
}
