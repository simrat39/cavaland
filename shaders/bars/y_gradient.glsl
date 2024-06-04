#version 410 core

uniform float[120] heights;
uniform float width;
uniform float height;
uniform uint num_bars;

void main() {
    vec3 normalize = vec3(255.f);

    vec3 color1 = vec3(69.f, 104.f, 220.f) / normalize;
    vec3 color2 = vec3(176.f, 106.f, 179.f) / normalize;

    vec2 uv = vec2(gl_FragCoord.x / width, gl_FragCoord.y / height);

    int idx = int(uv.x * num_bars);
    float b_width = (1.0 / num_bars); // Calculate the width of each bar

    float barStart = float(idx) * b_width;
    float barEnd = barStart + b_width;

    // Add spacing between bars
    float spacing = 0.001f; // Adjust the spacing as needed
    barStart += spacing;
    barEnd -= spacing;

    if (uv.x > barEnd) {
        discard; // Skip rendering for the spacing between bars
    }

    float bar_height = heights[idx];
    float gradient_mix_amount = uv.y;
    if (uv.y >= 0.01f) {
        gradient_mix_amount /= bar_height;
    }

    if (uv.x > barStart && (uv.y < bar_height || uv.y < 0.01f)) {
        gl_FragColor = vec4(mix(color1, color2, gradient_mix_amount), 1.0f);
    } else {
        discard; // Skip rendering for the area outside the bars
    }
}
