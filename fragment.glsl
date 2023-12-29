#version 410 core

in vec4 col;

out vec3 FragColor;

void main() {
  vec3 color1 = vec3(0.305f, 0.329f, 0.784f);
  vec3 color2 = vec3(0.56f, 0.580f, .984f);

  FragColor = mix(color1, color2, abs((col.x + 1.0f) / 2.0f));
}
