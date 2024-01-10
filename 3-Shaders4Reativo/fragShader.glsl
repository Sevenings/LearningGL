#version 330 core

#define PI 3.1415926535897932384626433832795

out vec4 FragColor;

in vec4 gl_FragCoord;
in vec3 aColor;

uniform vec2 u_dimensions;
uniform float time;
uniform float oscilation;

void main()
{
    vec4 outColor = vec4(aColor, 1);
    float angle = PI/2*sin(time/20);
    vec2 direction = vec2(cos(angle), sin(angle));
    direction = normalize(direction);
    float p = direction.x*gl_FragCoord.x + direction.y*gl_FragCoord.y;
    float q = direction.y*gl_FragCoord.x - direction.x*gl_FragCoord.y;
    float amp = sin(10*time + p/10 + oscilation/2*sin(2*oscilation*time)*sin((q/4+time)));
    if (amp < 0)
        amp = 0;
    amp = smoothstep(0.85, 0.95, amp);
    vec4 whiteSine = amp*vec4(1, 1, 1, 1);
    outColor += whiteSine;
    FragColor = outColor;
}   

