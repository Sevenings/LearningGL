#version 330 core

#define PI 3.1415926535897932384626433832795

out vec4 FragColor;

in vec2 TexCoord;
in vec3 ourColor;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float time;


vec3 hueShift(vec3 color, float hue) {
    const vec3 k = vec3(0.57735, 0.57735, 0.57735);
    float cosAngle = cos(hue);
    return vec3(color * cosAngle + cross(k, color) * sin(hue) + k * dot(k, color) * (1.0 - cosAngle));
}


void main()
{
    // FragColor =  mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
    vec4 color = texture(texture1, TexCoord);
    float path = (gl_FragCoord.x-gl_FragCoord.y)/2;
    color *= vec4(hueShift(vec3(1, 0, 0), 2*PI/1000*(time*300+path)), 0);
    color += vec4(0.1f, 0.1f, 0.1f, 0.1f);
    FragColor = color;
}   

