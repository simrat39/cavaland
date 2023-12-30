#version 410 core

in vec4 col;

out vec4 FragColor;

void main() {
  vec3 color1 = vec3(69.f, 104.f, 220.f);
  vec3 color2 = vec3(176.f, 106.f, 179.f);
  vec3 normalize = vec3(255.f);

  FragColor = vec4(mix(color1 / normalize, color2 / normalize, gl_FragCoord.y /
  (1920.f / 20.f)), 1.f);
   // FragColor = vec4();
}
