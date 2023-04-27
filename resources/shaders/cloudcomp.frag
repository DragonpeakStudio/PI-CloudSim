#version 330 core
out vec4 FragColor;
in vec2 texCoords;
uniform sampler2D image;
void main()
{
    vec4 base = texture(image, texCoords);
    FragColor = vec4(base);
}
