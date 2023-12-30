#version 410 core

layout (location = 0) in vec3 position;

void main() {
    gl_Position = vec4(position.x, position.y, 0.0f, 1.0f);
}
