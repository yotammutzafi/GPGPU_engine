#version 450

layout(binding = 1) uniform sampler2D texSampler;


layout(location = 0) in vec2 fragTexCoord;

layout(location = 0) out vec4 outColor;

void main() {
float d = 1.0f/200.0f;
    outColor =(vec4(0.0f,0.0f,0.0f,0.0f)
    +texture(texSampler, fragTexCoord+vec2(d,0.0f))
    +texture(texSampler, fragTexCoord+vec2(0.0f,d))
    +texture(texSampler, fragTexCoord+vec2(-d,0.0f))
    +texture(texSampler, fragTexCoord+vec2(0.0f,-d))
    +texture(texSampler, fragTexCoord+vec2(2.0f*d,0.0f))
    +texture(texSampler, fragTexCoord+vec2(0.0f,2.0f*d))
    +texture(texSampler, fragTexCoord+vec2(-2.0f*d,0.0f))
    +texture(texSampler, fragTexCoord+vec2(0.0f,-2.0f*d)))
    /8.0f
    ;
    
}