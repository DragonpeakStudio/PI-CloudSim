#version 330 core
in vec2 texCoords;
out vec4 FragColor;
uniform sampler3D densityField;
uniform sampler3D noiseKernal;

uniform float stepSize = .5;
uniform float lightStepSize = .1;
uniform float lightFar = 1.;
uniform float lightDensMult = .5;

uniform vec3 sunDir;
uniform vec3 sunCol;
uniform vec3 ambientCol;

uniform vec3 bboxMin;
uniform vec3 bboxMax;

uniform vec4 camPos;
uniform mat4 invProjView;
uniform ivec4 viewport;

uniform float time;

#include "lib/rand.slib"
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
float getDensity(vec3 p)
{
    p = (p-bboxMin)/(bboxMin-bboxMax);
    float d = texture(densityField, p).x;
    d -= texture(noiseKernal, p*5.).x*.5;
    d -= texture(noiseKernal, (p*7.)+3.58165).y*.25;
    d -= texture(noiseKernal, (p*12.)+7.273).z*.25;

    return max(d, 0.)*10.;
}
vec3 marchLight(Ray r, float near, float far)
{
    float dist = near;
    float totDens = 0.;
    while(dist < far)
    {
        vec3 pos = r.origin + r.dir*dist;;
        float dens = getDensity(pos);
        dist+=lightStepSize;
        totDens+=dens*lightStepSize;
    }
    return vec3(exp(-(totDens)*lightDensMult)*sunCol+ambientCol);
}
vec4 marchClouds(Ray r, float near, float far)
{
    float trans = 1.;
    vec3 light = vec3(0.);
    float dist = near;
    while(dist < far)
    {
        vec3 pos = r.origin + r.dir*dist;
        float dens = getDensity(pos);
        float st = stepSize;
        
        if(dens>.05)
        {
            vec2 dist =  bboxIntersection(r, bboxMin, bboxMax);
            trans *= exp(-dens);
            light += marchLight(Ray(pos, sunDir), .01, min(dist.y, lightFar))*dens*trans*st;
        }
        if(trans < .01)
        {
            trans =  0.;
            break;
        }
        dist+=st;

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
        vec4 dens = marchClouds(r, nearDist+=fpcg3d(vec3(texCoords.xy*viewport.zw, time)).x*stepSize, farDist);//TODO use blue noise for better dithering
        FragColor = vec4(dens);

    }

}