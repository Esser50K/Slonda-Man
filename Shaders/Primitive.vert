#version 330

layout (location = 0) in vec3 inVertexPosition;

void main()
{
    gl_Position = vec4(inVertexPosition.xyz, 1.0f);
}