// simple vertext shader
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCord;

out vec2 TexCord;

uniform mat4 mvp;

void main()
{
    // note that we read the multiplication from right to left
    gl_Position = mvp * vec4(aPos, 1.0);
    TexCord = aTexCord;
}
