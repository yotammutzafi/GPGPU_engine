#version 450

layout(set = 0,binding = 1) uniform UniformBufferObject_sunlight {
    vec3 direction;
    float arc;//this is how big the sun is in degrees(its the radis not the diameter)
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
}sunlight;

layout(set = 0,binding = 2) uniform UniformBufferObject_light_source {
    vec3 location;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}light_source[6];//6 is the number of light sources we can have(its an arbitrary number)

layout(set = 1,binding = 1) uniform sampler2D texSampler;

layout(location = 0) in vec3 fragColor;

layout(location = 0) out vec4 outColor;

void main() {
    outColor = vec4(fragColor.xy,0.5, 1.0);
}