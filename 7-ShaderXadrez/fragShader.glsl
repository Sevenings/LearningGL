#version 330 core

out vec4 FragColor;

in vec4 gl_FragCoord;

void main()
{
    float side = 80.0f;
    vec2 square = floor(gl_FragCoord.xy/side);
    if (int(square.x + square.y) % 2 == 0) {
        FragColor = vec4(0, 0, 0, 1);
    } else {
        FragColor = vec4(1, 1, 1, 1);
    }
}   

