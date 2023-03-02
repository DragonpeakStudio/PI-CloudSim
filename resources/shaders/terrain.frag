#version 330 core
out vec4 FragColor;
in vec4 normal;
in vec4 position;
in vec2 texCoords;
uniform sampler2D colourMap;
uniform vec3 lightDir;
uniform vec3 lightCol;
uniform vec3 ambientCol;
void main()
{

    vec4 baseCol = texture(colourMap, texCoords);
    float shaded = clamp(dot(normal.xyz, lightDir), 0., 1.);
    shaded *= clamp(baseCol.w, 0., 1.);
    vec3 light = shaded*lightCol+ambientCol;
    FragColor = vec4(baseCol.xyz*light,1.);
}
