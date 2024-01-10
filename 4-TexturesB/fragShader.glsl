#version 330 core

#define PI 3.1415926535897932384626433832795

out vec4 FragColor;

in vec2 TexCoord;
in vec3 ourColor;

uniform sampler2D texture1;
uniform float time;
uniform vec2 screenSize;

vec3 hueShift(vec3 color, float hue) {
    const vec3 k = vec3(0.57735, 0.57735, 0.57735);
    float cosAngle = cos(hue);
    return vec3(color * cosAngle + cross(k, color) * sin(hue) + k * dot(k, color) * (1.0 - cosAngle));
}


void main()
{
    float ttime = 0.3;
    float f = 0.5;
    float t = smoothstep(0.5-ttime/2, 0.5+ttime/2, fract(f*time));
    float ta = 0.5*floor(f*time) + 0.5*smoothstep(0.5-ttime/2, 0.5+ttime/2, fract(f*time));
    vec2 pos = 2*gl_FragCoord.xy/screenSize - 1;
    vec4 color = texture(texture1, TexCoord*2+vec2(0, t));

    float gray = dot(color.xyz, vec3(1, 1, 1))/3;
    gray = smoothstep(0.2, 0.3, gray);
    color = vec4(gray, gray, gray, 1); 

    // vec3 baseColor = vec3(1, 0, 0) + step(0.5, time)*vec3(-1, 0, 1);
    vec3 baseColor;
    float y = pos.y+ta;

    if ( pos.x < 0 && y > -ta) {
        baseColor = vec3(1, 0, 0);
    } else if (pos.x < 0 && y <= -ta) {
        baseColor = vec3(0, 1, 0);
    } else if (pos.x >= 0 && y > -ta) {
        baseColor = vec3(0, 0, 1);
    } else if (pos.x >= 0 && y <= -ta) {
        baseColor = vec3(1, 1, 0);
    }

    color *= vec4(hueShift(baseColor, floor(y+ta)), 1);

    FragColor = color;
}   

