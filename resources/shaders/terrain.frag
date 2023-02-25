#version 330 core
out vec4 FragColor;
in vec4 normal;
in vec2 texCoords;
uniform sampler2D colourMap;
uniform vec3 lightDir;
uniform vec3 lightCol;
uniform vec3 ambientCol;
void main()
{
    vec3 baseCol = texture(colourMap, texCoords).xyz;
    FragColor = vec4(baseCol*(clamp(dot(normal.xyz, lightDir), 0., 1.)*lightCol+ambientCol),1.);
}
