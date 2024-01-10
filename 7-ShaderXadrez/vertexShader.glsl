#version 330 core
layout (location = 0) in vec3 aPos; // the position variable has attribute position 0

uniform vec2 u_dimensions;

void main()
{
    vec3 pos = aPos; 

    float aspect = u_dimensions.y/u_dimensions.x;
    pos.x *= aspect;
    pos *= 0.8;

    gl_Position = vec4(pos, 1.0); // see how we directly give a vec3 to vec4's constructor
}
