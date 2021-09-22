#version 330 core
layout (location = 0) in vec3 aPos;

out vec4 vertexColor;
out vec3 pos;
uniform float xShift;

void main()
{
    gl_Position = vec4(aPos.x + xShift, aPos.yz, 1.0);
    pos = vec3(gl_Position.xyz);
}
