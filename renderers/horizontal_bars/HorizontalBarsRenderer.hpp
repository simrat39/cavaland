//
// Created by simrat39 on 12/29/23.
//

#pragma once

#include <epoxy/gl.h>
#include <glm/glm.hpp>
#include <array>
#include "../IRenderer.hpp"
#include "../../Shader.hpp"
#include "../../constants.hpp"

class HorizontalBarsRenderer: public IRenderer{
public:
   void pre_render() override;
   void render(double* data) override;
private:
    GLuint VAO;
    GLuint VBO;
    GLuint OFFSET_VBO;
    GLuint EBO;

    Shader* shader;

    std::array<glm::vec2, NUM_BARS> offsets{};
};
