#version 410 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aOffset;

out vec4 col;

void main() {
  vec2 adjusted_offset = aOffset;

  // Only adjust the height
  if (aPos.y == -1.f) {
    adjusted_offset.y = 0.f;
  }

  if (aPos.x == -1.f) {
    // Bottom and top left corners, adjust the initial offset for spacing
    adjusted_offset.x += 0.005f;
  } else {
    // Bottom and top right corners, adjust bar size
    adjusted_offset.x -= 0.005f;
  }

  gl_Position = vec4(aPos.x + (adjusted_offset.x), aPos.y + adjusted_offset.y, aPos.z, 1.0);

  col = gl_Position.xyzw;
}
