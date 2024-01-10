#version 330 core

#define PI 3.1415926535897932384626433832795

out vec4 FragColor;

in vec4 gl_FragCoord;
in vec3 aColor;

uniform vec2 u_dimensions;
uniform float time;

void main()
{
    vec4 outColor = vec4(aColor, 1);
    vec2 direction = vec2(2, 1);
    direction = normalize(direction);
    float p = direction.x*gl_FragCoord.x + direction.y*gl_FragCoord.y;
    float amp = sin(p/2 + 10*time);
    if (amp < 0)
        amp = 0;
    amp = pow(amp, 2);
    vec4 whiteSine = amp*vec4(1, 1, 1, 1);
    outColor += whiteSine;
    FragColor = outColor;
}   

