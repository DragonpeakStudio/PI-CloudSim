#version 330 core
layout (location = 0) in vec4 pos;
layout (location = 1) in vec4 nrm;
layout (location = 2) in vec4 uv;

out vec2 texCoords;
out vec4 normal;
uniform mat4 model = mat4(1.);
uniform mat4 view = mat4(1.);
uniform mat4 projection = mat4(1.);
void main()
{
    mat4 mvp = projection * view * model;
    gl_Position = mvp*vec4(pos);
    texCoords = uv.xy;
    normal = nrm;
}
