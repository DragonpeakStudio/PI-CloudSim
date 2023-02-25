#version 330 core
out vec4 FragColor;
in vec2 texCoords;
uniform sampler2D image;
uniform sampler2D depthImage;


void main()
{
    vec3 base = texture(image, texCoords).xyz;
    FragColor = vec4(pow(base, vec3(1./2.2)),1.);
}
