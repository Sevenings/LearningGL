#version 330 core
in vec2 pos;
out vec4 FragColor;

uniform vec4 greenTone;

void main()
{
    float d = length(pos);
    vec4 gradient = vec4(d, d, d, 0);
    FragColor = -gradient + greenTone;
}   

