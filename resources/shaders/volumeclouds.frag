#version 330 core
in vec2 texCoords;
out vec4 FragColor;
uniform sampler3D densityField;
uniform float stepSize = .1;
uniform vec3 bboxMin;
uniform vec3 bboxMax;
uniform vec4 camPos;
uniform mat4 invProjView;
uniform ivec4 viewport;
struct Ray
{
    vec3 origin;
    vec3 dir;
};

vec2 bboxIntersection(Ray r, vec3 boxMin, vec3 boxMax)//https://gist.github.com/DomNomNom/46bb1ce47f68d255fd5d
{
    vec3 tMin = (boxMin - r.origin) / r.dir;
    vec3 tMax = (boxMax - r.origin) / r.dir;
    vec3 t1 = min(tMin, tMax);
    vec3 t2 = max(tMin, tMax);
    float tNear = max(max(t1.x, t1.y), t1.z);
    float tFar = min(min(t2.x, t2.y), t2.z);
    return vec2(tNear, tFar);
}
vec4 marchClouds(Ray r, float near, float far)
{
    float trans = 1.;
    vec3 light = vec3(0.);
    float dist = near;
    while(dist < far)
    {
        vec3 pos = r.origin + r.dir*dist;
        pos/=(bboxMin-bboxMax);
        float dens = 1.1;
        if(dens>.01)
        {
            trans *= exp(-dens);
        }
        dist+=stepSize;

    }
    return vec4(light, 1.-trans);
}
void main()
{
    vec2 position = texCoords*2.-1.;
    Ray r =  Ray(camPos.xyz, (invProjView*vec4(position, 0., 1.)).xyz);
    vec2 dist =  bboxIntersection(r, bboxMin, bboxMax);
    FragColor = vec4(0);
    if(dist.x <= dist.y && (dist.x > 0. || dist.y > 0.))
    {
        float nearDist = max(.1, dist.x);
        float farDist = min(2000., dist.y);
        vec4 dens = marchClouds(r, nearDist, farDist);
        FragColor = vec4(nearDist,farDist,0,1);

    }

}
