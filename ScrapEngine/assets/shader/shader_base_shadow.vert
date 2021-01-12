#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 0) uniform UniformBufferObject {
    mat4 model;
    mat4 view;
    mat4 proj;
    mat4 lightSpace;
    vec3 lightPos;
} ubo;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec2 inTexCoord;
layout(location = 3) in vec3 inNormal;

layout(location = 0) out vec3 outNormal;
layout(location = 1) out vec3 outColor;
layout(location = 2) out vec2 fragTexCoord;
layout(location = 3) out vec3 outViewVec;
layout(location = 4) out vec3 outLightVec;
layout(location = 5) out vec4 outShadowCoord;

out gl_PerVertex {
    vec4 gl_Position;
};

const mat4 biasMat = mat4( 
    0.5, 0.0, 0.0, 0.0,
    0.0, 0.5, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0,
    0.5, 0.5, 0.0, 1.0 
);

void main() 
{
    outColor = inColor;
    outNormal = inNormal;
    fragTexCoord = inTexCoord;

    gl_Position = ubo.proj * ubo.view * ubo.model * vec4(inPosition, 1.0);
    
    vec4 pos = ubo.model * vec4(inPosition, 1.0);
    outNormal = mat3(ubo.model) * inNormal;
    outLightVec = normalize(ubo.lightPos - inPosition);
    outViewVec = -pos.xyz;			

    outShadowCoord = ( biasMat * ubo.lightSpace * ubo.model ) * vec4(inPosition, 1.0);	
}