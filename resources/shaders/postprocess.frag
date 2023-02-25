#version 330 core
out vec4 FragColor;
in vec2 texCoords;
uniform sampler2D image;
uniform sampler2D depthImage;


void main()
{

    vec4 base = texture(image, texCoords);
    vec3 col = mix(vec3(.6,.6,.9), base.xyz, base.w);
    FragColor = vec4(pow(col, vec3(1./2.2)),1.);
}
