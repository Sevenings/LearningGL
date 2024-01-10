#version 330 core
layout (location = 0) in vec3 aPos; // the position variable has attribute position 0
layout (location = 1) in vec3 aColor;

uniform float time;

out vec3 ourColor;

void main()
{
    vec3 pos = aPos;;
    vec2 baricenter = vec2(-0.5f, 0.5f) + vec2(0.5f,  0.5f) + vec2(0.0f, -0.5f);
    baricenter /= 3; 

    pos -= vec3(baricenter, 0);
    pos = vec3(pos.x*(cos(time)) + pos.y*(-sin(time)), pos.x*(sin(time)) + pos.y*(cos(time)), pos.z);
    pos += vec3(baricenter, 0);

    // vec3 tPos = vec3(0, 0.1*sin(time/3), 0);
    gl_Position = vec4(pos, 1.0); // see how we directly give a vec3 to vec4's constructor
    ourColor = aColor;
}
