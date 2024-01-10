#version 330 core

#define PI 3.1415926535897932384626433832795

out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D headTex;
uniform sampler2D boxTex;
uniform float time;
uniform vec2 screenSize;


void main()
{
    vec4 headcolor = texture(headTex, TexCoord);
    vec4 boxcolor = texture(boxTex, TexCoord);
    vec4 color = mix(boxcolor, headcolor, 0.3);
    FragColor = color;
}   

