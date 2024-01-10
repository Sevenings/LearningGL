#version 330 core
layout (location = 0) in vec3 aPos; // the position variable has attribute position 0
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

uniform vec2 screenSize;
uniform vec2 image_size;

out vec3 ourColor;
out vec2 TexCoord;
out vec3 pos;

void main()
{
    vec3 pos = aPos*2;
    float aspect = screenSize.y/screenSize.x;
    aspect /= image_size.y/image_size.x;
    pos.x *= aspect;

    gl_Position = vec4(pos, 1);

    ourColor = aColor;

    TexCoord = aTexCoord;
    
    pos = aPos;
}
