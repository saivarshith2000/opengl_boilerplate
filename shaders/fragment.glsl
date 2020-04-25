// Simple Fragment Shader
#version 330 core
in vec2 TexCord;

out vec4 FragColor;

uniform sampler2D texture1;

void main()
{
    FragColor = texture(texture1, TexCord);
}
