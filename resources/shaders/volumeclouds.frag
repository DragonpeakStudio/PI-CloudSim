#version 330 core
out vec4 FragColor;
uniform sampler3D densityField;
uniform float stepSize = 1.;
uniform vec3 bboxMin;
uniform vec3 bboxMax;
struct Ray
{
    vec3 origin;
    vec3 dir;
};
vec4 marchClouds(Ray r, float near, float far)
{
    float trans = 1.;
    vec3 light = vec3(0.);
    float dist = near;
    while(dist < far)
    {
        vec3 pos = r.origin + r.dir*dist;

    }
    return vec4(light, trans);

}
void main()
{
    //float dist = gl_FragCoord.z / gl_FragCoord.w;
    float near = .1; //TODO calc near and far from depth data
    float far = 500.;
    FragColor = vec4(1., 0, 0, 0.5);
}
