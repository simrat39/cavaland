#version 410 core

uniform float[120] heights;
uniform float width;
uniform float height;
uniform float num_bars;

void main() {
    vec3 color1 = vec3(69.f, 104.f, 220.f);
    vec3 color2 = vec3(176.f, 106.f, 179.f);
    vec3 normalize = vec3(255.f);

    float y_offset = 0.f;

    if (gl_FragCoord.x > width || gl_FragCoord.y > height) {
        discard;
    }

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

    float currentHeight = heights[idx];

    bool clearsYOffset = (uv.y > y_offset);
    bool shouldShowWhenSilent = (uv.y < (y_offset + 0.01f));
    bool isYinBetweenOffsetAndHeight = (uv.y < (currentHeight + y_offset));

    if ((uv.x > barStart && clearsYOffset && (isYinBetweenOffsetAndHeight || shouldShowWhenSilent))) {
        gl_FragColor = vec4(mix(color1/normalize, color2/normalize, uv.x), 1.0f);
    } else {
        discard; // Skip rendering for the area outside the bars
    }
}
