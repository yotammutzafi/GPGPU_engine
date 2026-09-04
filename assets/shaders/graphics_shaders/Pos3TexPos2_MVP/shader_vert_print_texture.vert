#version 450




layout(set = 0,binding = 0) uniform UniformBufferObject_vp {
    mat4 view;
    mat4 proj;
} vp;



layout(set = 1,binding = 0) uniform UniformBufferObject {
        mat4 scale;
		mat4 rotationANDoffset;
} ubo;




layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inTexcord;


layout(location = 0) out vec2 outTexcord;



void main() {
    gl_Position = vp.proj *vp.view* ubo.rotationANDoffset * ubo.scale * vec4(inPosition, 1.0);
 
    outTexcord = inTexcord;
}