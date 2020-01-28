#version 450
#extension GL_ARB_separate_shader_objects : enable

layout (location = 0) in vec3 inPos;

layout (binding = 0) uniform UBO
{
    mat4 model;
    mat4 depthMVP;
} ubo;

out gl_PerVertex
{
    vec4 gl_Position;
};

void main()
{
    gl_Position = ubo.depthMVP * ubo.model * vec4(inPos, 1.0);
}
