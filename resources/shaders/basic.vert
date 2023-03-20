#version 330 core
layout (location = 0) in vec2 pos;

out vec2 texCoords;

void main()
{
    gl_Position = vec4(pos,0.,1.);
    texCoords = pos/2. + .5;
}