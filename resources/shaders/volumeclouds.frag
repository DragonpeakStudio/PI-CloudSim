#version 330 core
in vec2 position;
out vec4 FragColor;
uniform sampler3D densityField;
uniform float stepSize = 1.;
uniform vec3 bboxMin;
uniform vec3 bboxMax;
uniform mat4 invProjView;
uniform ivec4 viewport;
struct Ray
{
    vec3 origin;
    vec3 dir;
};

vec2 bboxIntersection( Ray r, vec3 boxSize) 
{//https://iquilezles.org/articles/intersectors/
    vec3 m = 1.0/r.dir; 
    vec3 n = m*r.origin;   
    vec3 k = abs(m)*boxSize;
    vec3 t1 = -n - k;
    vec3 t2 = -n + k;
    float tN = max( max( t1.x, t1.y ), t1.z );
    float tF = min( min( t2.x, t2.y ), t2.z );
    if( tN>tF || tF<0.0) return vec2(-1.0); 
    return vec2( tN, tF );
}

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
    //https://stackoverflow.com/questions/42633685/glsl-how-to-calculate-a-ray-direction-using-the-projection-matrix
     vec4 near = vec4(
    2.0 * ( (gl_FragCoord.x - viewport[0]) / viewport[2] - 0.5),
    2.0 * ( (gl_FragCoord.y - viewport[1]) / viewport[3] - 0.5),
        0.0,
        1.0
    );
    near = invProjView * near ;
    vec4 far = near + invProjView[2] ;
    near.xyz /= near.w ;
    far.xyz /= far.w ;
    Ray r =  Ray(near.xyz, far.xyz-near.xyz) ;
    //end
    vec2 dist =  bboxIntersection(Ray(r.origin, r.dir), bboxMax-bboxMin);
    FragColor = vec4(0);
    if(dist.x != -1 && dist.y!=-1)
    {
        float nearDist = max(.1, dist.x);
        float farDist = min(2000., dist.y);
        FragColor = vec4(0, 0, 0, 1.);

    }

}
