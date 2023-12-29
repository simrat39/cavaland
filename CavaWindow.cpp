//
// Created by simrat39 on 12/26/23.
//

#include <iostream>
#include <gtkmm/glarea.h>
#include <epoxy/gl.h>
#include <glm/glm.hpp>
#include "CavaWindow.hpp"
#include "CavaService.hpp"
#include "Shader.hpp"

CavaWindow::CavaWindow() {
    cs = new CavaService{};
    cs->signal_data.connect(sigc::mem_fun(*this, &CavaWindow::on_data));

    gl_area.signal_realize().connect(sigc::mem_fun(*this, &CavaWindow::gl_on_realize));
    gl_area.signal_render().connect(sigc::mem_fun(*this, &CavaWindow::on_render), false);

    set_child(gl_area);

}

void CavaWindow::on_data(double *dataIn) {
    for (int i = 0; i < 30; ++i) {
       data[i] = dataIn[i];
    }
    gl_area.queue_render();
}

void CavaWindow::gl_on_realize() {
    gl_area.make_current();

    shader = new Shader{"../vertex.glsl", "../fragment.glsl"};

    float bar_width = (60.f / 800);

    // Pre Draw
    std::vector<GLfloat> vertices = {
            (-1) + bar_width, (-1.f) + 0.01f , 0.0f,  // top right
            (-1) + bar_width, -1.f           , 0.f,  // bottom right
            -1.f            , -1.f           , 0.f,  // bottom left
            -1.f            , (-1.f) + 0.01f , 0.0f   // top left
    };

    std::vector<GLuint> indices = {
            0, 1, 3,
            1, 2, 3
    };

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

    // This is after VAO cuz it needs the VAO
    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
    // This is after VBO cuz it needs the VBO
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);
    glEnableVertexAttribArray(0);

    for (int i = 0; i < 30; ++i) {
        offsets[i] = glm::vec2{i * (bar_width), 0};
    }

    GLuint OFFSET_VBO;
    glGenBuffers(1, &OFFSET_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, OFFSET_VBO);
    glBufferData(GL_ARRAY_BUFFER, offsets.size() * sizeof(glm::vec2), offsets.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glVertexAttribDivisor(1, 1);
    glEnableVertexAttribArray(1);

    glViewport(0, 0, get_width(), get_height());
}

bool CavaWindow::on_render(const Glib::RefPtr<Gdk::GLContext> &ctx) {
    // Rendering
//    glClearColor(0.117f, 0.117f, 0.180f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shader->use();

    for (int i = 0; i < 30; ++i) {
        offsets[i].y = data[i];
    }
    glBufferData(GL_ARRAY_BUFFER, offsets.size() * sizeof(glm::vec2), offsets.data(), GL_STATIC_DRAW);

    glBindVertexArray(VAO);
    glDrawElementsInstanced(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0, 30);

    //
//    SDL_GL_SwapWindow(sdl_window);
    return true;
}

CavaWindow::~CavaWindow() = default;
