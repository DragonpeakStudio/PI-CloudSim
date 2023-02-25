#version 330 core
out vec4 FragColor;
in vec4 normal;
in vec4 position;
in vec2 texCoords;
uniform sampler2D colourMap;
uniform sampler2D heightMap;
uniform vec3 lightDir;
uniform vec3 lightCol;
uniform vec3 ambientCol;
uniform float shadowSteps;
uniform float shadowFar;
uniform float shadowK;
uniform vec2 size;
void main()
{
    //simple raymarched shadows
    float r = 1.;
    float dep = 0.001;
    while(dep < shadowFar)
    {
        vec3 p = position.xyz+lightDir*dep + vec3(0,0,1);
        float data = texture(heightMap, (p.xy/size)+.5).x;
        
        r = min(r, shadowK*(p.z-data)/dep);
        dep += shadowSteps;
    }
    vec3 baseCol = texture(colourMap, texCoords).xyz;
    float shaded = clamp(dot(normal.xyz, lightDir), 0., 1.);
    shaded *= clamp(r, 0., 1.);
    vec3 light = shaded*lightCol+ambientCol;
    FragColor = vec4(baseCol*light,1.);
}
