#version 410 core

#ifndef PI
#define PI 3.141592653589793
#endif

uniform float[60] heights;
uniform float width;
uniform float height;

float sineInOut(float t) {
    return -0.5 * (cos(PI * t) - 1.0);
}

void main() {
    vec3 color1 = vec3(69.f, 104.f, 220.f);
    vec3 color2 = vec3(176.f, 106.f, 179.f);
    vec3 normalize = vec3(255.f);

    vec2 uv = vec2(gl_FragCoord.x / width, gl_FragCoord.y / height);

    int idx = int(uv.x * 60);
    float x_offset = 1 / 60.f;

    float localized_x_offset = uv.x - (idx * x_offset);

    // ease between these two, but how much? depends on X
    float bar_height = heights[idx];
    if (idx == 0) {
        bar_height = 0.0f;
    }

    float bar_height_next = heights[idx + 1];
    if (idx == 59) {
        bar_height_next = 0.0f;
    }

    float local_height = mix(bar_height, bar_height_next, sineInOut(localized_x_offset * 60.f));

    if (abs(uv.y - local_height) < 0.0025f) {
        gl_FragColor = vec4(0.f, 0.f, 0.f, 1.f);
    } else {
        if (uv.y < local_height) {
            gl_FragColor = vec4(mix(color1 / normalize, color2 / normalize, uv.x), uv.y / local_height);
        } else {
            discard;
        }
    }
}
