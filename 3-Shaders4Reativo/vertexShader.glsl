#version 330 core
layout (location = 0) in vec3 aPos; // the position variable has attribute position 0
layout (location = 1) in vec3 vColor;

out vec3 aColor;

uniform float time;
uniform vec2 u_dimensions;
uniform vec2 center;

void main()
{
    vec3 pos = aPos; 

    float t = time;
    // Pular 
/*
    pos -= vec3(center, 0);
    pos *= 0.1+0.9*(1+sin(time))/2;
    pos = vec3(pos.x*cos(t) - pos.y*sin(t), pos.x*sin(t) + pos.y*cos(t), pos.z);
    pos += vec3(center, 0);
*/

    float aspect = u_dimensions.y/u_dimensions.x;
    pos.x *= aspect;

    gl_Position = vec4(pos, 1.0); // see how we directly give a vec3 to vec4's constructor
    aColor = vColor;
}
